/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:46:30 by craabe            #+#    #+#             */
/*   Updated: 2026/01/12 15:52:18 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_node	*new_env_node(char *key, char *value)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
	{
		free(key);
		if (value)
			free(value);
		return (NULL);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env_node	*create_env_node(char *info)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 0;
	value = NULL;
	while (info[i] && info[i] != '=')
		i++;
	key = ft_substr(info, 0, i);
	if (!key)
		return (NULL);
	if (info[i] == '=')
	{
		value = ft_substr(info, i + 1, ft_strlen(info) - i - 1);
		if (!value)
		{
			free(key);
			return (NULL);
		}
	}
	return (new_env_node(key, value));
}

void	env_list_add_back(t_env_list *list, t_env_node *new_node)
{
	if (!list || !new_node)
		return ;
	if (!list->head)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = list->tail->next;
		list->tail->next = NULL;
	}
	list->size += 1;
}

// ft for changing the value of _ in env
int	set_filepath_envar(t_env_list *env_list, char *filepath)
{
	t_env_node	*current;
	t_env_node	*new_node;
	char		*underscore_key;
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
			// TODO: gc implementation!
			current->value = filepath_copy;
			return (0);
		}
		current = current->next;
	}
	underscore_key = ft_strdup("_");
	if (!underscore_key)
		return (-1);
	filepath_copy = ft_strdup(filepath);
	if (!filepath_copy)
	{
		free(underscore_key);
		return (-1);
	}
	new_node = new_env_node(underscore_key, filepath_copy);
	if (!new_node)
		return (-1);
	env_list_add_back(env_list, new_node);
	return (0);
}

void	free_env_list(t_env_list *env_list)
{
	t_env_node	*current;
	t_env_node	*next_node;

	if (!env_list)
		return ;
	current = env_list->head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next_node;
	}
	free(env_list);
}
