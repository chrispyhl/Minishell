/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_handle_externals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:44 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/23 14:22:14 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	handle_path_error(char *cmd, t_env_list *env)
{
	struct stat	info;
	int			ret;

	ret = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			ret = err_msg("No such file or directory", 127);
		else if (stat(cmd, &info) == 0 && S_ISDIR(info.st_mode))
			ret = err_msg("Is a directory", 126);
		else
			ret = err_msg("Permission denied", 126);
	}
	else
		ret = err_msg("command not found", 127);
	full_cleanup(env);
	return (ret);
}

static void	child_process(t_cmd_node *node, t_env_list *env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(node, env) == -1)
	{
		full_cleanup(env);
		exit(1);
	}
	execute_binary(node, env);
}

void	execute_binary(t_cmd_node *node, t_env_list *env)
{
	char	*path;
	char	**envp;
	int		i;

	i = 0;
	while (!node->cmd[i][0] && node->cmd[i + 1])
		i++;
	if (!node->cmd || !node->cmd[i] || !node->cmd[i][0])
	{
		full_cleanup(env);
		exit(0);
	}
	path = get_cmd_path(node->cmd[i], env); // Hole den Pfad der ausführbaren Datei
	if (!path)
		exit(handle_path_error(node->cmd[i], env)); // Wenn der Pfad nicht gefunden wird, Fehler behandeln
	envp = env_list_to_array(env); // Konvertiere die Umgebungsvariablenliste in ein Array für execve
	if (!envp)
	{
		full_cleanup(env);
		exit(1);
	}
	execve(path, (node->cmd) + i, envp); // Führe den Befe
	perror("chrispyshell: execve");
	full_cleanup(env);
	exit(126);
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
