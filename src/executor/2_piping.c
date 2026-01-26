/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_piping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:32:02 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 20:06:35 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"


static void	setup_child_io(t_pipe_info *info)
{
	if (info->prev_read != -1)
	{
		dup2(info->prev_read, STDIN_FILENO);
		close(info->prev_read);
	}
	if (info->node->next)
	{
		close(info->pipe_fds[0]);
		dup2(info->pipe_fds[1], STDOUT_FILENO);
		close(info->pipe_fds[1]);
	}
}

static void	close_other_heredoc_fds(t_cmd_list *list, t_cmd_node *current_node)
{
	t_cmd_node	*cmd;
	t_file_node	*file;

	if (!list)
		return ;
	cmd = list->head;
	while (cmd)
	{
		if (cmd != current_node && cmd->files) // nur andere Befehle
		{
			file = cmd->files->head;
			while (file)
			{
				if (file->redir_type == NODE_HEREDOC && file->heredoc_fd != -1)
					close(file->heredoc_fd);
				file = file->next;
			}
		}
		cmd = cmd->next;
	}
}

static void	pipe_child(t_cmd_list *list, t_pipe_info *info, t_env_list *env)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_io(info);
	close_other_heredoc_fds(list, info->node);
	if (handle_redirections(info->node, env) == -1)
	{
		full_cleanup(env);
		exit(1);
	}
	if (info->node->cmd_type == BUILTIN)
	{
		ret = execute_builtin(info->node, env, NULL);
		full_cleanup(env);
		exit(ret);
	}
	if (info->node->cmd == NULL || info->node->cmd[0] == NULL) // empty command
	{
		full_cleanup(env);
		exit(0);
	}
	execute_binary(info->node, env); // execute external command
}

static int	pipe_parent(int *pipe_fds, int *prev_read, t_cmd_node *node)
{
	if (*prev_read >= 0) // wenn es ein vorheriges Lese-Ende der Pipe gibt
		close(*prev_read); // schließe den vorherigen Lese-Ende der Pipe
	if (node->next)
	{
		if (pipe_fds[1] >= 0) // wenn es eine nächste Pipe gibt
			close(pipe_fds[1]); // schließe das Schreib-Ende der aktuellen Pipe im Parent
		*prev_read = pipe_fds[0]; // speichere das Lese-Ende für den nächsten Befehl
	}
	else
	{
		if (pipe_fds[0] >= 0)
			close(pipe_fds[0]); // schließe das Lese-Ende der aktuellen Pipe im Parent
	}
	return (0);
}

int	handle_piped_cmd(t_cmd_list *list, t_env_list *env)
{
	t_cmd_node	*current;
	t_pipe_info	info;
	int			pipe_fds[2];
	pid_t		pid;

	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	current = list->head;
	info.prev_read = -1;
	info.pipe_fds = pipe_fds;
	while (current)
	{
		if (current->next && pipe(pipe_fds) == -1) // Wenn noch ein Befehl folgt, erstelle eine Pipe
			return (perror("chrispyshell: pipe"), 1);
		pid = fork(); // Erstelle einen neuen Prozess
		if (pid == -1)
			return (perror("chrispyshell: fork"), 1);
		info.node = current; // Setze den aktuellen Knoten im Pipe-Info
		if (pid == 0)
			pipe_child(list, &info, env);
		pipe_parent(pipe_fds, &info.prev_read, current);
		current = current->next;
	}
	return (pid);
}
