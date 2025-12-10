/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:06:37 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/10 15:52:45 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	handle_cmd()
{
	if (e_cmd_type == CMD)
	{

	}
	if (e_cmd_type == BUILDIN)
}

int	executer_start(t_cmd_list *list)
{
	int			last_exit_status;
	int			status;
	t_cmd_node	*current_cmd;
	pid_t		pid1;

	if (!list || !list->head)
		return (0);
	status = 0;
	current_cmd = list->head;
	last_exit_status = 0;
	while (current_cmd)
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			// In / Out?
			last_exit_status = handle_cmd(current_cmd);
			exit(last_exit_status);
		}
		else if (pid1 < 0)
			return (1);
		else
		{
			waitpid(pid1, &status, 0);
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
		}
	}
	return (last_exit_status);
}
