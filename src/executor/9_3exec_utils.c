/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_3exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:17:15 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 18:09:48 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*find_path_in_dirs(char **dirs, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (dirs && dirs[i])
	{
		tmp = gc_strjoin(dirs[i], "/");
		full_path = gc_strjoin(tmp, cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env_list *env)
{
	char		*path_var;
	char		**dirs;
	char		*result;
	struct stat	path_stat;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			return (NULL);
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	dirs = ft_split(path_var, ':');
	result = find_path_in_dirs(dirs, cmd);
	free_string_array(dirs);
	return (result);
}
