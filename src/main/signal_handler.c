
#include "../../includes/minishell.h"

/*
ctrl + c = SIGINT
-> handled here
ctrl + \ = SIGQUIT
-> ignored here, handled in executor via waitpid function
*/

// necessary for ctrl + c (SIGINT) ft below
static void	handle_sigint(int sig)
{
	// update exit code to 2, the signal code for SIGINT
	g_signal = sig;
	// new line without overwriting prior input
	write(1, "\n", 1);
	// tells readline we are on a fresh line
	rl_on_new_line();
	// clear buffer
	rl_replace_line("", 0);
	// shows prompt chrispyshell$ again
	rl_redisplay();
}

// this is called upon CTRL + C
void	setup_signals(void)
{
	struct sigaction	sigact;

	// declare ft as our handler
	sigact.sa_handler = handle_sigint;
	// no flags, thank you
	sigact.sa_flags = 0;
	// empty mask
	sigemptyset(&sigact.sa_mask);
	// when CTRL + C (SIGINT = signal interrupt) comes in:
	sigaction(SIGINT, &sigact, NULL);
	// change it so handler just ignores signal now
	sigact.sa_handler = SIG_IGN;
	// this ignoring handler starts working for CTRL + \ (SIGQUIT)
	sigaction(SIGQUIT, &sigact, NULL);
	// this would otherwise crash the shell, so it has to be ignored
}

// TODO: final discussion about hardcoding 130
void	sync_exit_status(t_env_list *env)
{
	if (g_signal != 0)
	{
		env->exit_status = 128 + g_signal;
		g_signal = 0;
	}
}
