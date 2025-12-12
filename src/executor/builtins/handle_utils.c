/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:17:16 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 21:28:22 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

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

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
