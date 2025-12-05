/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:01:41 by craabe            #+#    #+#             */
/*   Updated: 2025/08/14 15:13:44 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_until_newline(char *line)
{
	int		i;
	int		j;
	char	*result;

	if (!line)
		return (NULL);
	if (ft_strchr(line, '\n') == NULL)
		return (ft_strdup(line));
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	i++;
	j = 0;
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = line[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

static int	ft_read_loop(int fd, char **buffer, char **line)
{
	int		bytes_read;
	char	*line_temp;

	bytes_read = 1;
	while (bytes_read > 0 && (!*line || ft_strchr(*line, '\n') == NULL))
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (0);
		(*buffer)[bytes_read] = '\0';
		if (*line == NULL || **line == '\0')
		{
			free(*line);
			*line = ft_strdup(*buffer);
		}
		else
		{
			line_temp = *line;
			*line = ft_strjoin(line_temp, *buffer);
			free(line_temp);
		}
	}
	if (bytes_read == 0 && (!*line || **line == '\0'))
		return (0);
	return (free(*buffer), 1);
}

static int	ft_read_prep(int fd, char **line, char *trim)
{
	char	*buffer;
	char	*newline_pt;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	if (ft_read_loop(fd, &buffer, line) == 0)
	{
		free(buffer);
		return (0);
	}
	newline_pt = ft_strchr(*line, '\n');
	if (newline_pt != NULL)
	{
		ft_strlcpy(trim, newline_pt + 1, ft_strlen(newline_pt + 1) + 1);
		*(newline_pt + 1) = '\0';
	}
	return (1);
}

static int	ft_trim_check(char *trim, char **line)
{
	if (trim[0] != '\0')
	{
		*line = ft_strdup(trim);
		trim[0] = '\0';
	}
	else
		*line = ft_strdup("");
	if (!*line)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	trim[FD_MAX][BUFFER_SIZE];
	char		*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	if (ft_trim_check(trim[fd], &line) == 0)
		return (NULL);
	if (ft_read_prep(fd, &line, trim[fd]) == 0)
	{
		trim[fd][0] = '\0';
		if (line)
			free(line);
		return (NULL);
	}
	result = ft_until_newline(line);
	free(line);
	if (!result)
		return (NULL);
	return (result);
}

// int	main(void)
// {
// 	int		txt_fd;
// 	char	*line;

// 	txt_fd = open("file.txt", O_RDONLY);
// 	if (txt_fd == -1)
// 	{
// 		perror("ERROR: Failed opening document.");
// 		return (1);
// 	}
// 	while ((line = get_next_line(txt_fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	if (close(txt_fd) < 0)
// 	{
// 		perror("ERROR: Failed closing document.");
// 		return (1);
// 	}
// 	return (0);
// }
