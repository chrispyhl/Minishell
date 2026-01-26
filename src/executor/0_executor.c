/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 19:03:23 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	close_last_hd(int *last_hd_fd)
{
	if (*last_hd_fd != -1) // Wenn ein letzter Heredoc-FD existiert
	{
		close(*last_hd_fd); // Schließe ihn
		*last_hd_fd = -1; // Setze den Wert zurück
	}
}

static int	process_heredoc_file(t_file_node *file, t_env_list *env, int *last)
{
	close_last_hd(last); // Schließe den vorherigen Heredoc-FD, falls vorhanden
	if (file->heredoc_fd != -1) // Wenn dieser Heredoc-FD bereits geöffnet ist
	{
		close(file->heredoc_fd); // Schließe ihn
		file->heredoc_fd = -1; // Setze den Wert zurück
	}
	file->heredoc_fd = fork_heredoc(file->filename, env, file->heredoc_quote); // Erstelle neuen Heredoc-FD
	if (file->heredoc_fd == -1) // Fehlerbehandlung
		return (-1);
	*last = file->heredoc_fd; // Aktualisiere den letzten Heredoc-FD
	return (0);
}

static int	process_cmd_heredocs(t_cmd_node *cmd, t_env_list *env)
{
	t_file_node	*file;
	int			last_hd_fd;

	if (!cmd || !cmd->files) // Keine Dateien zum Verarbeiten
		return (0);
	file = cmd->files->head;
	last_hd_fd = -1;
	while (file)
	{
		if (file->redir_type == NODE_HEREDOC)
		{
			if (process_heredoc_file(file, env, &last_hd_fd) == -1) // Fehlerbehandlung
				return (-1);
		}
		else if (file->redir_type == NODE_INPUT) // Wenn Input-Redirektion
			close_last_hd(&last_hd_fd); // Schließe den letzten Heredoc-FD
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

	if (!list || !list->head) // Prüfe, ob die Liste leer ist
		return ;
	if (pre_process_heredocs(list, env) == -1) // verarbeite alle Heredocs vor dem Ausführen der Befehle
	{
		close_all_heredocs(list); // wenn error, schließe alle Heredocs
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
	close_all_heredocs(list);
	setup_signals(); // restore signal handlers
}
