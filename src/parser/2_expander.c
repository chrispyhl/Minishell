/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:15 by craabe            #+#    #+#             */
/*   Updated: 2025/12/24 13:49:23 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

static int	remove_quotes(t_token_list *node)
{
	int					i;
	int					j;
	t_expander_state	state;
	char				*result;

	// TODO: replace with gc!
	// after removing the quotes, new string won't be larger than old one
	result = malloc((ft_strlen(node->token)) * sizeof(char));
	if (!result)
		return (-1);
	i = 0;
	j = 0;
	state = STATE_DEFAULT;
	while (node->token[i])
	{
		if (node->token[i] == '\'')
		{
			if (state == STATE_DEFAULT)
				state = STATE_SINGLE;
			else if (state == STATE_SINGLE)
				state = STATE_DEFAULT;
			else
			{
				result[j] = node->token[i];
				j++;
			}
			i++;
		}
		else if (node->token[i] == '\"')
		{
			if (state == STATE_DEFAULT)
				state = STATE_DOUBLE;
			else if (state == STATE_DOUBLE)
				state = STATE_DEFAULT;
			else
			{
				result[j] = node->token[i];
				j++;
			}
			i++;
		}
		else
			result[j++] = node->token[i++];
	}
	result[j] = '\0';
	free(node->token);
	node->token = result;
	return (0);
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
