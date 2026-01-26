/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_2_1more_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:43:08 by chris             #+#    #+#             */
/*   Updated: 2026/01/26 19:54:57 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	print_sorted_env(t_env_list *env)
{
	char	**env_arr;
	char	*temp;
	int		i;
	int		j;

	env_arr = env_list_to_array(env);
	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		j = i + 1;
		while (env_arr[j])
		{
			if (ft_strcmp(env_arr[i], env_arr[j]) > 0)
			{
				temp = env_arr[i];
				env_arr[i] = env_arr[j];
				env_arr[j] = temp;
			}
			j++;
		}
		print_export_line(env_arr[i]);
		i++;
	}
}

void	set_env_value(t_env_list *env, char *key, char *value)
{
	t_env_node	*current;
	t_env_node	*new;

	if (!env || !key)
		return ;
	current = env->head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env_node));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	env_list_add_back(env, new);
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

int	append_env_value(t_env_list *env, char *key, char *value)
{
	t_env_node	*current;
	char		*new_value;
	char		*base_value;

	if (!env || !key || !value)
		return (1);
	current = env->head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0) // Schlüssel gefunden
		{
			if (!value)
				return (1);
			base_value = current->value;
			if (!base_value)
				base_value = "";
			new_value = ft_strjoin(base_value, value);
			if (current->value)
				free(current->value);
			current->value = new_value;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	update_env_if_exists(t_env_list *env, char *key, char *value)
{
	t_env_node	*curr;

	curr = env->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (value)
			{
				if (curr->value)
					free (curr->value);
				curr->value = ft_strdup(value);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
