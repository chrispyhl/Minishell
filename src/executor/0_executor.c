/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/27 12:02:22 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	close_last_hd(int *last_hd_fd)
{
	if (*last_hd_fd != -1)
	{
		close(*last_hd_fd);
		*last_hd_fd = -1;
	}
}

static int	p_hd_file(t_file_node *file, t_env_list *env, int *last)
{
	close_last_hd(last);
	if (file->heredoc_fd != -1)
	{
		close(file->heredoc_fd);
		file->heredoc_fd = -1;
	}
	file->heredoc_fd = fork_heredoc(file->filename, env, file->heredoc_quote);
	if (file->heredoc_fd == -1)
		return (-1);
	*last = file->heredoc_fd;
	return (0);
}

static int	process_cmd_heredocs(t_cmd_node *cmd, t_env_list *env)
{
	t_file_node	*file;
	int			last_hd_fd;

	if (!cmd || !cmd->files)
		return (0);
	file = cmd->files->head;
	last_hd_fd = -1;
	while (file)
	{
		if (file->redir_type == NODE_HEREDOC)
		{
			if (p_hd_file(file, env, &last_hd_fd) == -1)
				return (-1);
		}
		else if (file->redir_type == NODE_INPUT)
			close_last_hd(&last_hd_fd);
		file = file->next;
	}
	return (0);
}

static int	pre_process_heredocs(t_cmd_list *list, t_env_list *env)
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
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
	close_all_heredocs(list);
	setup_signals();
}
