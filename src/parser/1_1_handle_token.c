/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_1_handle_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:20:05 by craabe            #+#    #+#             */
/*   Updated: 2026/01/19 12:20:14 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	check_if_word_char(char c)
{
	return (c != '|' && c != '<' && c != '>' && c != ' ' && c != '\t');
}

int	handle_token_word(char *input, t_token_list *token_list, int *i)
{
	char			*node_content;
	int				j;
	t_token_node	*new_node;
	char			*seg;

	seg = input + *i; // seg = segment of the string, starting from index i
	j = 0;
	// skip until something that does not belong to the word is encountered
	while (seg[j] && check_if_word_char(seg[j]) == 1)
	{
		// if the loop found a double/single quote, we enter quote mode
		// --> all characters are escaped up until the next quote
		// includes edge case handling for (example) echo "A"B
		// --> creates two nodes: echo, "A"B
		// --> bash would output AB --> "A"B will be refined in expander
		if ((seg[j] == '\"' || seg[j] == '\'') && find_quote_end(seg, &j) == -1)
			return (-1);
		else
			j++;
	}
	// create a new node containing seg up until the undesired character
	// since ft_substr copies with the condition (i < len), it stops before j
	node_content = gc_substr(seg, 0, j);
	if (!node_content)
		return (-1);
	// this creates a new token_list node with the substr and it's token category (WORD)
	new_node = create_token_node(node_content, T_WORD);
	if (!new_node)
		return (-1);
	// i gets incremeted by j so the lexer ft continues after the word
	*i += j;
	// the node gets added to the master token_list
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
	node_content = NULL; // safety initialization to avoid garbage value
	if (create_redir_node_content(seg, &node_content, &redir_type) == -1)
		return (-1);
	new_node = create_token_node(node_content, redir_type);
	if (!new_node)
		return (-1);
	(*i) += ft_strlen(node_content);
	token_list_add_back(token_list, new_node);
	return (0);
}
