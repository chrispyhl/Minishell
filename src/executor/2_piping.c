/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_piping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:32:02 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/07 16:30:53 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	setup_pipes(int *pipe_fds, int prev_read, t_cmd_node *node)
{
	(void)prev_read; // not used here but could be useful for extensions
	if (node->next)
	{
		if (pipe(pipe_fds) == -1)
		{
			return (perror("chrispyshell: pipe"), -1);
		}
	}
	return (0);
}

static void	pipe_child(int *pipe_fds, int prev_read, t_cmd_node *node, t_env_list *env)
{
	int	status;

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
	status = handle_single_cmd(node, env);
	gc_free();
	exit(status);
}

static int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	wait_res;

	last_status = 0;
	while (1)
	{
		wait_res = waitpid(-1, &status, 0); // wenn waitpid -1 ist sind alle Kinderprozesse beendet
		if (wait_res <= 0) // wenn alle childs beendet sind,
			break ; // beende die Schleife
		if (wait_res == last_pid) // wenn es der letzte Prozess ist,
			last_status = status; // speichere seinen Status
	}
	return (get_exit_status(last_status)); // nur der Exit-Status des letzten Befehls wird zurückgegeben
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
	pid_t		pid;
	t_cmd_node	*current;
	int			pipe_fds[2]; // 0: read end, 1: write end
	int			prev_read;

	current = list->head;
	prev_read = -1;
	while (current)
	{
		if (setup_pipes(pipe_fds, prev_read, current) == -1)
			break ;
		pid = fork();
		if (pid == -1)
			return (perror("chrispyshell: fork"), 1);
		if (pid == 0)
			pipe_child(pipe_fds, prev_read, current, env);
		pipe_parent(pipe_fds, &prev_read, current);
		current = current->next;
	}
	return (wait_for_children(pid));
}
