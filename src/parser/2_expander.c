/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:15 by craabe            #+#    #+#             */
/*   Updated: 2026/01/13 15:15:18 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	expander(t_token_list *token_list, t_env_list *env_list)
{
	t_token_node		*current;

	current = token_list->head;
	while (current)
	{
		if (current->token_type == T_WORD)
		{
			if (check_state(current, env_list) == -1)
				return (-1);
			// if there is a double or single quote inside
			if (ft_strchr(current->token, '\'') != NULL
				|| ft_strchr(current->token, '\"') != NULL)
				if (remove_quotes(current) == -1)
					return (-1);
		}
		current = current->next;
	}
	return (0);
}
