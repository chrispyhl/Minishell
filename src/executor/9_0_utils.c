/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:10 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 18:54:57 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	handle_signal_output(int status)
{
	if (WIFSIGNALED(status)) // wenn durch Signal beendet
	{
		if (WTERMSIG(status) == SIGINT) // Ctrl+C
			write(1, "\n", 1); // neue Zeile ausgeben
		else if (WTERMSIG(status) == SIGQUIT) // Ctrl+'\'
			write(1, "Quit (core dumped)\n", 19);
	}
}

void	wait_for_all(t_env_list *env, pid_t last_pid)
{
	int	status;
	int	last_status;
	int	res;

	last_status = 0;
	if (last_pid == -1)
		return ;
	while (1)
	{
		res = waitpid(-1, &status, 0); // auf beliebigen Kindprozess warten
		if (res <= 0) // Fehler oder keine Kindprozesse mehr
			break ;
		if (res == last_pid) // letzter Prozess
			last_status = status; // Status speichern
		handle_signal_output(status); // Signalausgabe behandeln
	}
	env->exit_status = get_exit_status(last_status); // Exit-Status setzen
}

int	err_msg(char *msg, int status)
{
	ft_putstr_fd("chrispyshell: ", 2);
	ft_putendl_fd(msg, 2);
	return (status);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
