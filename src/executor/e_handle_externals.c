/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_handle_externals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:44 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/09 15:46:42 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

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

static void	child_process(t_cmd_node *node, t_env_list *env)
{
	char	*path;
	char	**envp;

	if (handle_redirections(node, env) == -1)
	{
		gc_free();
		exit(1);
	}
	path = get_cmd_path(node->cmd[0], env);
	if (!path)
		exit(handle_path_error(node->cmd[0]));
	envp = env_list_to_array(env);
	if (!envp || execve(path, node->cmd, envp) == -1)
	{
		perror("chrispyshell: execve");
		gc_free();
		exit(126);
	}
}

int	handle_external_cmd(t_cmd_node *node, t_env_list *env)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (perror("chrispyshell: fork"), 1);
	if (pid == 0)
		child_process(node, env);
	return (pid);
}
