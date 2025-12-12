/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:11:53 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 20:52:13 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include <limits.h>

int	handle_cd(t_cmd_node *node, t_env_list *env)
{
	char	*path;

	if (!node->cmd[1])
	{
		path = get_env_value(env, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: Env->HOME not set\n", 2);
			return (1); // error msg
		}
	}
	else
	{
		path = node->cmd[1];
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
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

int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, 1);
		free (cwd);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("getcwd failed to get working directory\n", 2);
	return (0);
}

// int	handle_export(t_cmd_node *node)
// {
	
// }

// int	handle_unset(t_cmd_node *node)
// {
	
// }
