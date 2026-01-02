/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_handle_externals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:44 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/02 17:34:00 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

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

static int	handle_path_error(char *cmd)
{
	struct stat	info;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (err_msg(cmd, "No such file or directory", 127));
		if (stat(cmd, &info) == 0 && S_ISDIR(info.st_mode))
			return (err_msg(cmd, "is a directory", 126));
		return (err_msg(cmd, "Permission denied", 126));
	}
	return (err_msg(cmd, "command not found", 127));
}

int	handle_external_cmd(t_cmd_node *node, t_env_list *env)
{
	char		*path;
	pid_t		pid;
	int			status;

	path = get_cmd_path(node->cmd[0], env);
	if (!path)
		return (handle_path_error(node->cmd[0]));
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
