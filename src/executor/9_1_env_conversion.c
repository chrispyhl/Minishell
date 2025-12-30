/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_1_env_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:01:24 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/30 16:08:36 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static char	*combine_env_str(t_env_node *node)
{
	char	*tmp;
	char	*res;

	if (!node->key)
		return (NULL);
	if (!node->value)
		return (gc_strdup(node->key));
	tmp = gc_strjoin(node->key, "=");
	res = gc_strjoin(tmp, node->value);
	return (res);
}

char	**env_list_to_array(t_env_list *env)
{
	char		**envp;
	t_env_node	*curr;
	int			i;

	if (!env)
		return (NULL);
	envp = ft_malloc((env->size + 1) * sizeof(char *), 1);
	if (!envp)
		return (NULL);
	curr = env->head;
	i = 0;
	while (curr)
	{
		envp[i] = combine_env_str(curr);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
