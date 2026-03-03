/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:34 by craabe            #+#    #+#             */
/*   Updated: 2026/01/27 12:00:46 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	find_quote_end(char *seg, int *j)
{
	char	type;

	type = seg[*j];
	(*j)++;
	while (seg[*j] && seg[*j] != type)
		(*j)++;
	if (seg[*j] == type)
		(*j)++;
	else
	{
		ft_putstr_fd("chrispyshell: quote not closed\n", 2);
		return (-1);
	}
	return (0);
}

int	create_redir_node_content(char *seg, char **node_content,
		t_token_type *redir_type)
{
	if (seg[0] == '<' && seg[1] == '<')
	{
		*node_content = gc_strdup("<<");
		*redir_type = T_HEREDOC;
	}
	else if (seg[0] == '>' && seg[1] == '>')
	{
		*node_content = gc_strdup(">>");
		*redir_type = T_REDIR_APP;
	}
	else if (seg[0] == '<')
	{
		*node_content = gc_strdup("<");
		*redir_type = T_REDIR_IN;
	}
	else if (seg[0] == '>')
	{
		*node_content = gc_strdup(">");
		*redir_type = T_REDIR_OUT;
	}
	if ((!*node_content))
		return (-1);
	return (0);
}
