/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_externals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:44 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/29 21:13:09 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

static void	child_process(char *path, t_cmd_node *node, t_env_list *env)
{
	char	**envp;

	if (handle_redirections(node, env) == -1)
	{
		gc_free();
		exit(1);	
	}
	envp = env_list_to_array(env);
	if (!envp || execve(path, node->cmd, envp) == -1)
	{
		perror("minishell: execve");
		gc_free();
		exit(126);
	}
}

int	handle_external_cmd(t_cmd_node *node, t_env_list *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = get_cmd_path(node->cmd[0], env);
	if (!path)
		return (err_msg(node->cmd[0], "command not found", 127));
	pid = fork();
	if (pid == -1)
	{
		gc_free();
		return (perror("minishell: fork"), 1);
	}
	if (pid == 0)
		child_process(path, node, env);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
