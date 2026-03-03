/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_handle_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:20:05 by craabe            #+#    #+#             */
/*   Updated: 2026/01/27 12:00:33 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	check_if_word_char(char c)
{
	return (c != '|' && c != '<' && c != '>' && c != ' ' && c != '\t');
}

static t_token_node	*create_word_token_node(char *seg, int j)
{
	char			*node_content;
	t_token_node	*new_node;

	node_content = gc_substr(seg, 0, j);
	if (!node_content)
		return (NULL);
	new_node = create_token_node(node_content, T_WORD);
	if (!new_node)
		return (NULL);
	return (new_node);
}

int	handle_token_word(char *input, t_token_list *token_list, int *i)
{
	int				j;
	char			*seg;
	t_token_node	*new_node;

	seg = input + *i;
	j = 0;
	while (seg[j] && check_if_word_char(seg[j]) == 1)
	{
		if (seg[j] == '\"' || seg[j] == '\'')
		{
			if (find_quote_end(seg, &j) == -1)
				return (-1);
		}
		else
			j++;
	}
	new_node = create_word_token_node(seg, j);
	if (!new_node)
		return (-1);
	*i += j;
	token_list_add_back(token_list, new_node);
	return (0);
}

int	handle_token_pipe(t_token_list *token_list, int *i)
{
	char			*node_content;
	t_token_node	*new_node;

	node_content = gc_strdup("|");
	if (!node_content)
		return (-1);
	new_node = create_token_node(node_content, T_PIPE);
	if (!new_node)
		return (-1);
	(*i)++;
	token_list_add_back(token_list, new_node);
	return (0);
}

int	handle_token_redir(char *input, t_token_list *token_list, int *i)
{
	char			*node_content;
	t_token_node	*new_node;
	char			*seg;
	t_token_type	redir_type;

	seg = input + *i;
	node_content = NULL;
	if (create_redir_node_content(seg, &node_content, &redir_type) == -1)
		return (-1);
	new_node = create_token_node(node_content, redir_type);
	if (!new_node)
		return (-1);
	(*i) += ft_strlen(node_content);
	token_list_add_back(token_list, new_node);
	return (0);
}
