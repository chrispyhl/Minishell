/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_handle_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:11:53 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/08 12:31:56 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	update_env_pwd(t_env_list *env, char *old_pwd)
{
	char	new_pwd[1024];

	process_export_arg(env, gc_strjoin("OLDPWD=", old_pwd));
	if (getcwd(new_pwd, sizeof(new_pwd)))
		process_export_arg(env, gc_strjoin("PWD=", new_pwd));
}

void	print_export_line(char *line)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (line[i] && line[i] != '=')
		ft_putchar_fd(line[i++], 1);
	if (line[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(&line[i + 1], 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
}

int	handle_cd(t_cmd_node *node, t_env_list *env)
{
	char	*path;
	char	old_pwd[1024];

	if (node->cmd[1] && node->cmd[2])
		return (err_msg("cd", "too many arguments", 1));
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	if (!node->cmd[1])
	{
		path = get_env_value(env, "HOME");
		if (!path || !*path)
			return (err_msg("cd", "HOME not set", 1));
	}
	else
		path = node->cmd[1];
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
	while (node->cmd[i] && !ft_strncmp(node->cmd[i], "-n", 3))
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
