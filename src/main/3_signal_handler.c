/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_signal_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:19:56 by craabe            #+#    #+#             */
/*   Updated: 2026/01/27 12:06:56 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	sigact;

	sigact.sa_handler = handle_sigint;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	sigaction(SIGINT, &sigact, NULL);
	sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, NULL);
}

void	sync_exit_status(t_env_list *env)
{
	if (g_signal != 0)
	{
		env->exit_status = 128 + g_signal;
		g_signal = 0;
	}
}
