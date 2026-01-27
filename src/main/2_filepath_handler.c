/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filepath_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:19:48 by craabe            #+#    #+#             */
/*   Updated: 2026/01/19 12:19:51 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_env_node	*set_underscore_key(char *filepath)
{
	t_env_node	*new_node;
	char		*underscore_key;
	char		*filepath_copy;

	underscore_key = ft_strdup("_");
	if (!underscore_key)
		return (NULL);
	filepath_copy = ft_strdup(filepath);
	if (!filepath_copy)
	{
		free(underscore_key);
		return (NULL);
	}
	new_node = new_env_node(underscore_key, filepath_copy);
	if (!new_node)
		return (NULL);
	return (new_node);
}

// ft for changing the value of _ in env
int	set_filepath_envar(t_env_list *env_list, char *filepath)
{
	t_env_node	*current;
	t_env_node	*new_node;
	char		*filepath_copy;

	current = env_list->head;
	while (current)
	{
		// look for the key from parameter
		if (ft_strcmp(current->key, "_") == 0)
		{
			filepath_copy = ft_strdup(filepath);
			if (!filepath_copy)
				return (-1);
			// if key already has value, free it
			if (current->value)
				free(current->value);
			current->value = filepath_copy;
			return (0);
		}
		current = current->next;
	}
	new_node = set_underscore_key(filepath);
	if (!new_node)
		return (-1);
	env_list_add_back(env_list, new_node);
	return (0);
}

// the contents of argv[0] depend on how the program was called
// ./chrispyshell --> relative path in argv
// /home/example/chrispyshell --> absolute path
// to unify, this ft will return the full path in any case
char	*get_filepath(char *path)
{
	char	cwd[PATH_MAX];
	char	*result;
	char	*temp;

	// if it starts with a slash, it is abolute already
	if (path[0] == '/')
		// returning ft_strdup so this also returns malloced string
		return (ft_strdup(path));
	// if it starts with ., the path is relative
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (NULL);
	temp = ft_strjoin(cwd, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, path);
	free(temp);
	return (result);
}
