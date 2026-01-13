/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_piping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:32:02 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/12 12:03:39 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	pipe_child(int *pipe_fds, int prev_read, t_cmd_node *node, t_env_list *env)
{
	if (prev_read != -1) // Wenn es nicht der erste Befehl ist...
	{
		dup2(prev_read, STDIN_FILENO); // ...nimm den Input vom vorherigen Befehl
		close(prev_read);
	}
	if (node->next) // wenn noch ein Befehl folgt...
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO); // ...schreibe den Output in die Pipe
		close(pipe_fds[1]);
	}
	if (handle_redirections(node, env) == -1) // Redictions überschreiben die Pipes (haben Vorrang) z.b. bei "<" oder ">"
	{
		gc_free();
		exit(1);
	}
	exit(handle_single_cmd(node, env));
}

static int	pipe_parent(int *pipe_fds, int *prev_read, t_cmd_node *node)
{
	if (*prev_read != -1)
		close(*prev_read); // schließe den vorherigen Lese-Ende der Pipe
	if (node->next)
	{
		close(pipe_fds[1]); // schließe das Schreib-Ende der aktuellen Pipe im Parent
		*prev_read = pipe_fds[0]; // speichere das Lese-Ende für den nächsten Befehl
	}
	return (0);
}

int	handle_piped_cmd(t_cmd_list *list, t_env_list *env)
{
	t_cmd_node	*current;
	int			pipe_fds[2]; // 0: read end, 1: write end
	int			prev_read;
	pid_t		pid;

	current = list->head;
	prev_read = -1;
	while (current)
	{
		if (current->next && pipe(pipe_fds) == -1)
			return (perror("chrispyshell: pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("chrispyshell: fork"), 1);
		if (pid == 0)
			pipe_child(pipe_fds, prev_read, current, env);
		pipe_parent(pipe_fds, &prev_read, current);
		current = current->next;
	}
	return (pid);
}
