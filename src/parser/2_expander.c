/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:15 by craabe            #+#    #+#             */
/*   Updated: 2025/12/22 17:15:55 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// small helper ft to avoid clutter in if statement in expander ft
static int	check_var_start(char c)
{
	if (ft_isalnum(c) == 1 || c == '_' || c == '?')
		return (1);
	return (0);
}

static t_expander_state	get_state(char letter, t_expander_state mode_curr)
{
	if (mode_curr == STATE_DEFAULT)
	{
		if (letter == '\'')
			return (STATE_SINGLE);
		if (letter == '\"')
			return (STATE_DOUBLE);
	}
	if (mode_curr == STATE_SINGLE)
	{
		if (letter == '\'')
			return (STATE_DEFAULT);
	}
	if (mode_curr == STATE_DOUBLE)
	{
		if (letter == '\"')
			return (STATE_DEFAULT);
	}
	// if nothing fits, original value is returned
	return (mode_curr);
}

int	expander(t_token_list *token_list, t_env_list *env_list)
{
	t_token_list		*current;
	int					i;
	t_expander_state	state;

	current = token_list;
	while (current)
	{
		if (current->token_type == T_WORD)
		{
			i = 0;
			state = STATE_DEFAULT;
			while (current->token[i])
			{
				state = get_state(current->token[i], state);
				// we encounter a $-sign
				// --> are we in single-quote-mode?
				// no? is it a viable envar? (depending on following char)
				// 1) yes = expand; 2) no = just increment, keep as is
				if (current->token[i] == '$' && state != STATE_SINGLE
					&& check_var_start(current->token[i + 1]) == 1)
				{
					if (expand_token(current, env_list, &i) == -1)
						return (-1);
				}
				else
					i++;
			}
		}
		current = current->next;
	}
	return (0);
}
