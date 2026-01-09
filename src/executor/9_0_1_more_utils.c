/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_1_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:19:57 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/08 13:07:31 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void handle_wait_status(int status, t_env_list *env)
{
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		env->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: (core dumped)\n", 2);
	}
	sync_exit_status(env);
}
