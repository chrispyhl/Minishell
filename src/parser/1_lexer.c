/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:37:01 by craabe            #+#    #+#             */
/*   Updated: 2026/01/27 11:59:58 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	token_handler_picker(char *input, t_token_list *token_list, int *i)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (handle_token_redir(input, token_list, i) == -1)
			return (-1);
	}
	else if (input[*i] == '|')
	{
		if (handle_token_pipe(token_list, i) == -1)
			return (-1);
	}
	else
	{
		if (handle_token_word(input, token_list, i) == -1)
			return (-1);
	}
	return (0);
}

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
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			break ;
		if (token_handler_picker(input, token_list, &i) == -1)
			return (NULL);
	}
	return (token_list);
}
