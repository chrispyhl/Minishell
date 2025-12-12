/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:17:16 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 20:57:48 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
