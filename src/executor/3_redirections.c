/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:48:54 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 19:54:42 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	apply_node_redir(t_file_node *current, t_env_list *env)
{
	int	fd;

	if (current->redir_type == NODE_HEREDOC)
	{
		if (current->heredoc_fd != -1) // if heredoc fd is valid
		{
			if (dup2(current->heredoc_fd, STDIN_FILENO) == -1) // STDIN bekommt Heredoc-FD Inhalt
				return (perror("chrispyshell: dup2"), -1);
			close(current->heredoc_fd); // schließe den Heredoc-FD nach dem Duplizieren
			current->heredoc_fd = -1;
		}
		return (0);
	}
	fd = open_file(current->filename, current->redir_type); // Datei öffnen (z.B. "output.txt", >)
	if (fd == -1)
	{
		env->exit_status = 1;
		return (-1);
	}
	apply_fd_redir(fd, current->redir_type); // Datei-Deskriptor auf die entsprechende Standarddatei umleiten
	return (0);
}

static int	validate_redirections(t_file_list *files, t_env_list *env)
{
	t_file_node	*current;
	int			fd;

	current = files->head;
	while (current)
	{
		if (current->redir_type == NODE_HEREDOC
			&& current->heredoc_fd == -1) // heredoc nicht geöffnet
			return (env->exit_status = 1, -1); // Fehler
		if (current->redir_type != NODE_HEREDOC)
		{
			fd = open_file(current->filename, current->redir_type);
			if (fd == -1)
				return (env->exit_status = 1, -1);
			close(fd);
		}
		current = current->next;
	}
	return (0);
}

static t_file_node	*find_last_input(t_file_list *files)
{
	t_file_node	*current;
	t_file_node	*last_input;

	last_input = NULL;
	current = files->head;
	while (current)
	{
		if (current->redir_type == NODE_INPUT
			|| current->redir_type == NODE_HEREDOC) // consider heredoc as input
			last_input = current; // update last_input
		current = current->next;
	}
	return (last_input);
}

static int	apply_redirections(t_file_list *files, t_file_node *last_input,
		t_env_list *env)
{
	t_file_node	*current;

	current = files->head;
	while (current)
	{
		if (!((current->redir_type == NODE_INPUT
					|| current->redir_type == NODE_HEREDOC)
				&& current != last_input)) // skip all input or heredoc except last one
		{// (output and append are always applied, input/heredoc only the last one)
			if (apply_node_redir(current, env) == -1) // apply redirection on all others
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	handle_redirections(t_cmd_node *node, t_env_list *env)
{
	if (!node || !node->files) // Wenn keine Dateien zum Verarbeiten
		return (0);
	if (validate_redirections(node->files, env) == -1) // Alles validieren
		return (-1);
	return (apply_redirections(node->files, find_last_input(node->files), env)); // Redirections anwenden
}
