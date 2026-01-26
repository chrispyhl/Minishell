/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_3_1_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:29:58 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 19:54:10 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	open_file(char *filename, int type)
{
	int			fd;

	if (!filename || !*filename)
		return (-1);
	if (check_is_directory(filename, type))
		return (-1);
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

void	apply_fd_redir(int fd, int type)
{
	if (type == NODE_INPUT)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	check_is_directory(char *filename, int type)
{
	struct stat	info;

	if ((type == NODE_OUTPUT || type == NODE_APPEND) // nur für Output und Append
		&& stat(filename, &info) == 0 && S_ISDIR(info.st_mode)) // stat erfolgreich und ist Verzeichnis
	{ // (stat holt meta daten -> 0, -1) || S_ISDIR prüft ob Verzeichnis
		ft_putstr_fd("chrispyshell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (1);
	}
	return (0);
}
