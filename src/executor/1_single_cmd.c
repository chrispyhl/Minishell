/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_single_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:52:49 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/30 15:24:34 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	builtin_redir(t_cmd_node *node, t_env_list *env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(node, env) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	ret = execute_builtin(node, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
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
	if (node->cmd_type == BUILTIN)
		return (builtin_redir(node, env));
	if (node->cmd_type == EXTERNAL)
		return (execute_external(node, env));
	return (0);
}
