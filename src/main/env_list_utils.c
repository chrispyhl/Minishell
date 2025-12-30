/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:46:30 by craabe            #+#    #+#             */
/*   Updated: 2025/12/11 17:50:42 by craabe           ###   ########.fr       */
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

// TODO: replace with gc functionality
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
