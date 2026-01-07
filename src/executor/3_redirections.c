/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:48:54 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/06 10:25:39 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	get_var_len(char *str)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[len]))
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static char	*expand_heredoc_line(char *line, t_env_list *env)
{
	char	*new_line;
	char	*var_name;
	char	*var_value;
	int		i;

	i = 0;
	new_line = gc_strdup("");
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
		{
			var_name = gc_substr(line, i + 1, get_var_len(&line[i + 1]));
			var_value = get_env_value(env, var_name);
			if (var_value)
				new_line = gc_strjoin(new_line, var_value);
			i += ft_strlen(var_name) + 1;
		}
		else
		{
			char tmp[2] = {line[i++], '\0'};
			//new_line = gc_strjoin(new_line, gc_substr(line, i++, 1));
			new_line = gc_strjoin(new_line, tmp);
		}
	}
	return (new_line);
}

static int	open_file(char *filename, int type)
{
	int			fd;
	struct stat	info;

	if ((type == NODE_OUTPUT || type == NODE_APPEND) 
			&& stat(filename, &info) == 0 && S_ISDIR(info.st_mode))
	{
		ft_putstr_fd("chrispyshell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (-1);
	}
	fd = -1;
	if (type == NODE_INPUT)
		fd = open(filename, O_RDONLY);
	else if (type == NODE_OUTPUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == NODE_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("chrispyshell: ", 2);
		perror(filename);
	}
	return (fd);
}

static void	handle_heredoc(char *delimiter, t_env_list *env)
{
	char	*line;
	char	*expanded;
	int		pipe_fds[2];
	size_t	d_len;

	if (pipe(pipe_fds) == -1)
		return (perror("chrispyshell: pipe heredoc"));
	d_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == d_len && ft_strncmp(line, delimiter, d_len) == 0))
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, env);
		ft_putendl_fd(expanded, pipe_fds[1]);
		free(line);
	}
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
}

int	handle_redirections(t_cmd_node *node, t_env_list *env)
{
	t_file_node	*current;
	int			fd;

	if (!node || !node->files || !node->files->head)
		return (0);
	current = node->files->head;
	while (current)
	{
		if (current->redir_type == NODE_HEREDOC)
			handle_heredoc(current->filename, env);
		else
		{
			fd = open_file(current->filename, current->redir_type);
			if (fd == -1)
				return (-1);
			if (current->redir_type == NODE_INPUT)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		current = current->next;
	}
	return (0);
}
