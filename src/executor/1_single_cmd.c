/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_single_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:52:49 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/07 15:10:02 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	update_underscore(t_env_list *env, char **cmd)
{
	int			i;

	if (!env || !cmd || !cmd[0])
		return ;
	i = 0;
	while(cmd[i])
		i++;
	set_env_value(env, "_", cmd[i - 1]);
}

static int	builtin_redir(t_cmd_node *node, t_env_list *env)
{
	int	saved_io[2];
	int	ret;

	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	if (handle_redirections(node, env) == -1)
	{
		close(saved_io[0]);
		close(saved_io[1]);
		return (1);
	}
	ret = execute_builtin(node, env);
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
	return (ret);
}

int	execute_external(t_cmd_node *node, t_env_list *env)
{
	return (handle_external_cmd(node, env));
}

int	execute_builtin(t_cmd_node *node, t_env_list *env)
{
	if (ft_strncmp(*node->cmd, "cd", 3) == 0)
		return (handle_cd(node, env));
	if (ft_strncmp(*node->cmd, "echo", 5) == 0)
		return (handle_echo(node));
	if (ft_strncmp(*node->cmd, "pwd", 4) == 0)
		return (handle_pwd());
	if (ft_strncmp(*node->cmd, "export", 7) == 0)
		return (handle_export(node, env));
	if (ft_strncmp(*node->cmd, "unset", 6) == 0)
		return (handle_unset(node, env));
	if (ft_strncmp(*node->cmd, "env", 4) == 0)
		return (handle_env(env));
	if (ft_strncmp(*node->cmd, "exit", 5) == 0)
		return (handle_exit(node));
	return (1);
}

int	handle_single_cmd(t_cmd_node *node, t_env_list *env)
{
	int	saved_io[2];

	if (!node->cmd || !node->cmd[0])
	{
		saved_io[0] = dup(STDIN_FILENO);
		saved_io[1] = dup(STDOUT_FILENO);
		if (handle_redirections(node, env) == -1)
		{
			dup2(saved_io[0], STDIN_FILENO);
			dup2(saved_io[1], STDOUT_FILENO);
			return (close(saved_io[0]), close(saved_io[1]), 0);
		}
		dup2(saved_io[0], STDIN_FILENO);
		dup2(saved_io[1], STDOUT_FILENO);
		return (close(saved_io[0]), close(saved_io[1]), 0);
	}
	update_underscore(env, node->cmd);
	if (node->cmd_type == BUILTIN)
		return (builtin_redir(node, env));
	else if (node->cmd_type == EXTERNAL)
		return (execute_external(node, env));
	return (0);
}
