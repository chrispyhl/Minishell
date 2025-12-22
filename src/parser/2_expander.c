/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:15 by craabe            #+#    #+#             */
/*   Updated: 2025/12/22 16:21:37 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"



int	expander(t_token_list *token_list, t_env_list *env_list)
{
	t_token_list	*current;
	int				i;

	current = token_list;
	while (current)
	{
		if (current->token_type == T_WORD)
		{
			i = 0;
			while (current->token[i])
			{
				if (process_token(current, env_list, &i) == -1)
					return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}
