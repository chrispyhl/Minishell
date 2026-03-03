/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_handle_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:11:53 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/27 12:06:40 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	update_env_pwd(t_env_list *env, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	set_env_value(env, "OLDPWD", old_pwd);
	set_env_value(env, "PWD", new_pwd);
	free(new_pwd);
}

static int	is_valid_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	handle_cd(t_cmd_node *node, t_env_list *env)
{
	char	*path;
	char	old_pwd[1024];

	if (node->cmd[1] && node->cmd[2])
		return (err_msg("too many arguments", 1));
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	path = node->cmd[1];
	if (!path || !*path)
		return (err_msg("HOME not set", 1));
	if (path && ft_strncmp(path, "-", 2) == 0)
	{
		path = get_env_value(env, "OLDPWD");
		if (!path)
			return (err_msg("OLDPWD not set", 1));
		ft_putendl_fd(path, 1);
	}
	if (chdir(path) != 0)
		return (perror("chrispyshell: cd"), 1);
	update_env_pwd(env, old_pwd);
	return (0);
}

int	handle_echo(t_cmd_node *node)
{
	int		i;
	int		n;

	n = 1;
	i = 1;
	while (node->cmd[i] && is_valid_n(node->cmd[i]))
	{
		n = 0;
		i++;
	}
	while (node->cmd[i])
	{
		ft_putstr_fd(node->cmd[i], 1);
		if (node->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	handle_export(t_cmd_node *node, t_env_list *env)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!node->cmd[1])
	{
		print_sorted_env(env);
		return (0);
	}
	i = 1;
	while (node->cmd[i])
	{
		if (process_export_arg(env, node->cmd[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
