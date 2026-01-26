/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:48:54 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 13:45:38 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	apply_fd_redir(int fd, int type)
{
	if (type == NODE_INPUT)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
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

static int	apply_node_redir(t_file_node *current, t_env_list *env)
{
	int	fd;

	if (current->redir_type == NODE_HEREDOC)
	{
		if (current->heredoc_fd != -1)
		{
			if (dup2(current->heredoc_fd, STDIN_FILENO) == -1)
				return (perror("chrispyshell: dup2"), -1);
			close(current->heredoc_fd); // child no longer needs the heredoc FD after dup2
			current->heredoc_fd = -1;
		}
		return (0);
	}
	fd = open_file(current->filename, current->redir_type);
	if (fd == -1)
	{
		env->exit_status = 1;
		return (-1);
	}
	apply_fd_redir(fd, current->redir_type);
	return (0);
}

int	handle_redirections(t_cmd_node *node, t_env_list *env)
{
	t_file_node	*current;
	t_file_node	*last_input;

	if (!node || !node->files)
		return (0);
	// Find the last INPUT or HEREDOC redirection (they conflict)
	// Only the last one should be applied
	last_input = NULL;
	current = node->files->head;
	while (current)
	{
		if (current->redir_type == NODE_INPUT || current->redir_type == NODE_HEREDOC)
			last_input = current;
		current = current->next;
	}
	// Apply redirections, but skip non-last input/heredoc
	current = node->files->head;
	while (current)
	{
		if (!((current->redir_type == NODE_INPUT || current->redir_type == NODE_HEREDOC)
			&& current != last_input))
		{
			if (apply_node_redir(current, env) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
