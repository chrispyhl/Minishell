/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_2_1more_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:43:08 by chris             #+#    #+#             */
/*   Updated: 2026/01/12 16:01:59 by cpohl            ###   ########.fr       */
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
			current->value = ft_strdup(value);
			gc_add(current->value);
			return ;
		}
		current = current->next;
	}
	new = ft_calloc(1, sizeof(t_env_node));
	gc_add(new);
	new->key = ft_strdup(key);
	gc_add(new->key);
	new->value = ft_strdup(value);
	gc_add(new->value);
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
