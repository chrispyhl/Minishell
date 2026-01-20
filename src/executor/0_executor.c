/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/20 16:05:22 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	wait_for_all(t_env_list *env, pid_t last_pid)
{
	int	status;
	int	last_status;
	int	res;
	int	was_signaled;

	last_status = 0;
	was_signaled = 0;
	if (last_pid == -1)
		return ;
	while (1)
	{
		res = waitpid(-1, &status, 0); // wenn waitpid -1 ist sind alle Kinderprozesse beendet
		if (res <= 0) // wenn alle childs beendet sind,
			break ; // beende die Schleife
		if (res == last_pid) // wenn es der letzte Prozess ist,
			last_status = status; // speichere seinen Status
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) // wenn ein Prozess durch SIGINT beendet wurde
			was_signaled = 1; // merke es
	}
	if (was_signaled)
		write(1, "\n", 1); // neue Zeile bei SIGINT
	if (WIFSIGNALED(last_status))
		env->exit_status = WTERMSIG(last_status) + 128;
	else
		env->exit_status = WEXITSTATUS(last_status);
}

static int	process_cmd_heredocs(t_cmd_node *cmd, t_env_list *env)
{
	t_file_node	*file;

	file = NULL;
	if (cmd->files)
		file = cmd->files->head;
	while (file)
	{
		if (file->redir_type == NODE_HEREDOC)
		{
			if (file->heredoc_fd != -1)
				close(file->heredoc_fd);
			file->heredoc_fd = fork_heredoc(file->filename, env);
			if (file->heredoc_fd == -1)
				return (-1);
		}
		file = file->next;
	}
	return (0);
}

int	pre_process_heredocs(t_cmd_list *list, t_env_list *env)
{
	t_cmd_node	*current;

	current = list->head;
	while (current)
	{
			if (process_cmd_heredocs(current, env) == -1)
					return (-1);
			current = current->next;
	}
	return (0);
}

static void	close_all_heredocs(t_cmd_list *list)
{
	t_cmd_node	*cmd;
	t_file_node	*file;

	cmd = list->head;
	while (cmd)
	{
		file = NULL;
		if (cmd)
		{
			if (cmd->files)
				file = cmd ->files->head;
		}
		while (file)
		{
			if (file->heredoc_fd != -1)
			{
				close(file->heredoc_fd);
				file->heredoc_fd = -1;
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}

void	execute_command_list(t_cmd_list *list, t_env_list *env)
{
	t_cmd_node	*current;
	pid_t		last_pid;

	if (!list || !list->head)
		return ;
	if (pre_process_heredocs(list, env) == -1)
	{
		close_all_heredocs(list);
		return ;
	}
	signal(SIGINT, SIG_IGN); // ignore SIGINT in parent during processing
	signal(SIGQUIT, SIG_IGN); // ignore SIGQUIT in parent during processing
	current = list->head;
	if (!current)
		return ;
	if (list->size == 1 && current->cmd_type == BUILTIN)
		env->exit_status = handle_single_cmd(current, env);
	else
	{
		last_pid = handle_piped_cmd(list, env);
		wait_for_all(env, last_pid);
	}
	setup_signals(); // restore signal handlers
	close_all_heredocs(list);
}
