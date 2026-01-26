/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:11:12 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 19:25:56 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	heredoc_loop(char *del, t_env_list *env, int pipe_fd, int heredoc_quote)
{
	char	*line;
	size_t	d_len;

	d_len = ft_strlen(del);
	close_inherited_fds(pipe_fd);
	g_signal = 0;
	signal(SIGINT, heredoc_sigint_handler); // set custom SIGINT handler (if Ctrl+C -> heredoc_handler)
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line) // readline returned NULL (EOF or Signal)
			handle_heredoc_eof(del, env, pipe_fd);
		if ((ft_strlen(line) == d_len && ft_strncmp(line, del, d_len) == 0)) // delimiter reached
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, env, pipe_fd, heredoc_quote);
	}
	rl_clear_history();
	heredoc_cleanup_and_exit(env, pipe_fd, 0);
}

static int	heredoc_wait(pid_t pid, int *pipe_fds, t_env_list *env)
{
	int	status;

	waitpid(pid, &status, 0);
	setup_signals(); // restore signal handlers
	rl_on_new_line();
	rl_replace_line("", 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (pipe_fds[0]); // return read end of the pipe
	close(pipe_fds[0]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		env->exit_status = 130;
	}
	return (-1);
}

int	fork_heredoc(char *delimiter, t_env_list *env, int heredoc_quote)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1) // create pipe
		return (-1);
	signal(SIGINT, SIG_IGN); // ignore SIGINT in parent during heredoc
	pid = fork();
	if (pid == 0) // Child process
	{
		close(pipe_fds[0]); // Close read end in child (we only write)
		heredoc_loop(delimiter, env, pipe_fds[1], heredoc_quote);
	}
	close(pipe_fds[1]); // Close write end in parent
	return (heredoc_wait(pid, pipe_fds, env));
}
