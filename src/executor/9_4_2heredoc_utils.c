/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_4_2heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:08:45 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 19:18:34 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	close_inherited_fds(int keep_fd)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fd != keep_fd)
			close(fd);
		fd++;
	}
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	close(STDIN_FILENO);
}

void	heredoc_cleanup_and_exit(t_env_list *env, int pipe_fd, int status)
{
	if (pipe_fd >= 0)
		close(pipe_fd);
	free_env_list(env);
	gc_free();
	exit(status);
}

void	handle_heredoc_eof(char *del, t_env_list *env, int pipe_fd)
{
	if (g_signal == SIGINT)
		heredoc_cleanup_and_exit(env, pipe_fd, 130);
	ft_putstr_fd("chrispyshell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(del, 2);
	ft_putstr_fd("')\n", 2);
	heredoc_cleanup_and_exit(env, pipe_fd, 0);
}

void	process_heredoc_line(char *line, t_env_list *env, int pipe_fd, int hd_quote)
{
	char	*expanded;

	expanded = expand_heredoc_line(line, env, hd_quote); // expand line
	ft_putendl_fd(expanded, pipe_fd); // write to pipe
	free(line);
	free(expanded);
}
