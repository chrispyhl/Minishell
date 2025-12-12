/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_more_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:55:53 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 21:57:41 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

void remove_env_node(t_env_list *env, char *key)
{
	t_env_node	*current;
	t_env_node	*prev;
	size_t		len;

	if (!env || !env->head)
		return ;

	current = env->head;
	prev = NULL;
	len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->key, key, len + 1) == 0)
		{
			if (prev == NULL)
				env->head = current->next;
			else
				prev->next = current->next;
			env->size--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}
