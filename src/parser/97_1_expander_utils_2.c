/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_1_expander_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:20:36 by craabe            #+#    #+#             */
/*   Updated: 2026/01/19 12:20:38 by craabe           ###   ########.fr       */
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

static void	handle_single_quote(t_expander_state *state, char *result, int *i,
		int *j)
{
	if (*state == STATE_DEFAULT)
		*state = STATE_SINGLE;
	else if (*state == STATE_SINGLE)
		*state = STATE_DEFAULT;
	else
	{
		result[*j] = '\'';
		(*j)++;
	}
	(*i)++;
}

static void	handle_double_quote(t_expander_state *state, char *result, int *i,
		int *j)
{
	if (*state == STATE_DEFAULT)
		*state = STATE_DOUBLE;
	else if (*state == STATE_DOUBLE)
		*state = STATE_DEFAULT;
	else
	{
		result[*j] = '\"';
		(*j)++;
	}
	(*i)++;
}

int	remove_quotes(t_token_node *node)
{
	int					i;
	int					j;
	t_expander_state	state;
	char				*result;

	// after removing the quotes, new string won't be larger than old one
	result = ft_malloc(ft_strlen(node->token) + 1, sizeof(char));
	if (!result)
		return (-1);
	i = 0;
	j = 0;
	state = STATE_DEFAULT;
	while (node->token[i])
	{
		if (node->token[i] == '\'')
			handle_single_quote(&state, result, &i, &j);
		else if (node->token[i] == '\"')
			handle_double_quote(&state, result, &i, &j);
		else
			result[j++] = node->token[i++];
	}
	result[j] = '\0';
	node->token = result;
	return (0);
}

int	check_state(t_token_node *current, t_env_list *env_list)
{
	int					i;
	t_expander_state	state;

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
	return (0);
}
