/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_single_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:52:49 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 15:56:15 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	builtin_redir(t_cmd_node *node, t_env_list *env)
{
	int	saved_io[2];
	int	ret;

	saved_io[0] = dup(STDIN_FILENO); // Speichere die original STDIN
	saved_io[1] = dup(STDOUT_FILENO); // Speichere die original STDOUT
	if (handle_redirections(node, env) == -1)
	{
		dup2(saved_io[0], STDIN_FILENO);
		dup2(saved_io[1], STDOUT_FILENO);
		close(saved_io[0]);
		close(saved_io[1]);
		return (1);
	}
	ret = execute_builtin(node, env, saved_io);
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
	return (ret);
}

int	execute_builtin(t_cmd_node *node, t_env_list *env, int saved_io[2])
{
	if (ft_strncmp(*node->cmd, ".", 2) == 0)
		return (err_msg("filename argument required", 1));
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
		return (handle_exit(node, env, saved_io));
	return (1);
}

int	handle_single_cmd(t_cmd_node *node, t_env_list *env)
{
	pid_t	pid;

	while (node->cmd && node->cmd[0] && node->cmd[0][0] == '\0' && node->cmd[1])
		node->cmd++;
	if (!node->cmd || !node->cmd[0] || node->cmd[0][0] == '\0')
	{
		if (handle_redirections(node, env) == -1)
			env->exit_status = 1;
		else
			env->exit_status = 0;
		return (env->exit_status);
	}
	update_underscore(env, node->cmd);
	if (node->cmd_type == BUILTIN)
		env->exit_status = builtin_redir(node, env);
	else
	{
		pid = handle_external_cmd(node, env);
		wait_for_all(env, pid);
	}
	sync_exit_status(env);
	return (env->exit_status);
}
