/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:37:01 by craabe            #+#    #+#             */
/*   Updated: 2026/01/13 15:06:07 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	token_handler_picker(char *input, t_token_list *token_list, int *i)
{
	// catch redirs
	if (input[*i] == '<' || input[*i] == '>')
	// this helper function populates token_node and increments i
	{
		if (handle_token_redir(input, token_list, i) == -1)
			return (-1);
	}
	// catch pipes
	else if (input[*i] == '|')
	{
		// this helper function populates token_node and increments i
		if (handle_token_pipe(token_list, i) == -1)
			return (-1);
	}
	// catch everything else
	else
	{
		// this helper function populates token_node and increments i
		if (handle_token_word(input, token_list, i) == -1)
			return (-1);
	}
	return (0);
}

// the tokenizer
t_token_list	*lexer(char *input)
{
	int				i;
	t_token_list	*token_list;

	i = 0;
	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	while (input[i])
	{
		// skip whitespaces
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			break ;
		if (token_handler_picker(input, token_list, &i) == -1)
			return (NULL);
	}
	return (token_list);
}
