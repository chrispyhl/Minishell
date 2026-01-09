/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/09 15:52:34 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

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
		res = waitpid(-1, &status, 0); // wenn waitpid -1 ist sind alle Kinderprozesse beendet
		if (res <= 0) // wenn alle childs beendet sind,
			break ; // beende die Schleife
		if (res == last_pid) // wenn es der letzte Prozess ist,
			last_status = status; // speichere seinen Status
	}
	if (WIFEXITED(last_status))
		env->exit_status = WEXITSTATUS(last_status); // nur der Exit-Status des letzten Befehls wird zurückgegeben
	else if (WIFSIGNALED(last_status))
		env->exit_status = 128 + WTERMSIG(last_status);
}

void	execute_command_list(t_cmd_list *list, t_env_list *env)
{
	t_cmd_node	*current;
	pid_t		last_pid;

	current = list->head;
	if (!current)
		return ;
	if (list->size == 1 && current->cmd_type == BUILTIN)
	{
		env->exit_status = handle_single_cmd(current, env);
		return ;
	}
	last_pid = handle_piped_cmd(list, env);
	wait_for_all(env, last_pid);
}
