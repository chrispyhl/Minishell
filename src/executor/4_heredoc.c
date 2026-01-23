/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:11:12 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/23 13:51:31 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static char	*expand_heredoc_line(char *line, t_env_list *env, int heredoc_quote)
{
	char	*new_line;
	char	*old;
	char	*temp;
	int		i;

	i = 0;
	new_line = ft_strdup("");
	if (heredoc_quote)
	{
		free(new_line);
		return (ft_strdup(line));
	}
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_')) // Variable detected
			new_line = append_var(line, &i, env, new_line);
		else
		{
			temp = ft_substr(line, i++, 1);
			old = new_line;
			new_line = ft_strjoin(new_line, temp); // Copy regular character
			free(old);
			free(temp);
		}
	}
	return (new_line);
}

static void	heredoc_cleanup_and_exit(t_env_list *env, int pipe_fd, int status)
{
	if (pipe_fd >= 0)
		close(pipe_fd);
	free_env_list(env);
	gc_free();
	exit(status);
}

static void	heredoc_loop(char *del, t_env_list *env, int pipe_fd, int heredoc_quote)
{
	char	*line;
	char	*expanded;
	size_t	d_len;

	d_len = ft_strlen(del);
	signal(SIGINT, SIG_DFL);  // set signal handler for SIGINT to default
	signal(SIGQUIT, SIG_IGN); // ignore SIGQUIT
	while (1)
	{
		line = readline("> "); // prompt for heredoc input
		if (!line)             // EOF encountered
			break ;
		if ((ft_strlen(line) == d_len && ft_strncmp(line, del, d_len) == 0))
														// delimiter matched
		{
			free(line); // free the line before breaking
			break ;
		}
		expanded = expand_heredoc_line(line, env, heredoc_quote);
		// expand variables in the line
		ft_putendl_fd(expanded, pipe_fd);
		// write expanded line to pipe
		free(line);
		free(expanded);
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
		close(pipe_fds[0]); // Close read end in child
		heredoc_loop(delimiter, env, pipe_fds[1], heredoc_quote);
	}
	close(pipe_fds[1]); // Close write end in parent
	return (heredoc_wait(pid, pipe_fds, env));
}
