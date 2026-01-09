/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_2env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:17:16 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/08 12:36:03 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

char	*get_env_value(t_env_list *env, char *key)
{
	t_env_node	*current;
	size_t		key_len;

	if (!env || !key)
		return (NULL);
	current = env->head;
	key_len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->key, key, key_len + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	env_add_back(t_env_list *env, char *key, char *value)
{
	t_env_node	*new_node;

	new_node = ft_malloc(1, sizeof(t_env_node));
	if (!new_node)
		return ;
	new_node->key = gc_strdup(key);
	if (value)
		new_node->value = gc_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (!env->head)
	{
		env->head = new_node;
		env->tail = new_node;
	}
	else
	{
		env->tail->next = new_node;
		env->tail = new_node;
	}
	env->size++;
}

static void	unlink_env_node(t_env_list *env, t_env_node *curr, t_env_node *prev)
{
	if (!prev)
		env->head = curr->next;
	else
		prev->next = curr->next;
	if (curr == env->tail)
		env->tail = prev;
	env->size--;
}

void	remove_env_node(t_env_list *env, char *key)
{
	t_env_node	*curr;
	t_env_node	*prev;
	size_t		len;

	if (!env || !env->head || !key)
		return ;
	curr = env->head;
	prev = NULL;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len + 1) == 0)
		{
			unlink_env_node(env, curr, prev);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	is_valid_env_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
