/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:37:01 by craabe            #+#    #+#             */
/*   Updated: 2025/12/15 08:59:54 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/parser.h"

// TODO: does not handle open quote (echo "Hello ); should it?
// for now, this ft prints and returns error when quote is unclosed

static int	handle_token_word(char *input, t_token_list **token_list, int *i)
{
	char			*node_content;
	int				j;
	t_token_list	*new_node;
	char			*seg;

	seg = input + *i; // seg = segment of the string, starting from index i
	j = 0;
	// skip until something that does not belong to the word is encountered
	while (seg[j] && seg[j] != '|' && seg[j] != '<' && seg[j] != '>'
		&& seg[j] != ' ' && seg[j] != '\t')
	{
		// if the loop found a double/single quote, we enter quote mode
		// --> all characters are escaped up until the next quote
		// includes edge case handling for (example) echo "A"B
		// --> creates two nodes: echo, "A"B
		// --> bash would output AB --> "A"B will be refined in expander
		if (seg[j] == '\"' || seg[j] == '\'')
		{
			if (find_quote_end(seg, &j) == -1)
				return (-1);
		}
		else
			j++;
	}
	// create a new node containing seg up until the undesired character
	// since ft_substr copies with the condition (i < len), it stops before j
	node_content = ft_substr(seg, 0, j);
	if (!node_content)
		return (-1);
	// this creates a new list node with the substr and it's token category (WORD)
	new_node = create_token_node(node_content, T_WORD);
	if (!new_node)
	{
		free(node_content);
		return (-1);
	}
	// i gets incremeted by j so the lexer ft continues after the word
	*i += j;
	// the node gets added to the master list
	token_list_add_back(token_list, new_node);
	return (0);
}

static int	handle_token_pipe(t_token_list **token_list, int *i)
{
	char			*node_content;
	t_token_list	*new_node;

	node_content = ft_strdup("|");
	if (!node_content)
		return (-1);
	new_node = create_token_node(node_content, T_PIPE);
	if (!new_node)
	{
		free(node_content);
		return (-1);
	}
	(*i)++;
	token_list_add_back(token_list, new_node);
	return (0);
}

static int	handle_token_redir(char *input, t_token_list **token_list, int *i)
{
	char			*node_content;
	t_token_list	*new_node;
	char			*seg;
	t_token_type	redir_type;

	seg = input + *i;
	node_content = NULL; // safety initialization to avoid garbage value
	if (create_redir_node_content(seg, &node_content, &redir_type) == -1)
		return (-1);
	new_node = create_token_node(node_content, redir_type);
	if (!new_node)
	{
		free(node_content);
		return (-1);
	}
	(*i) += ft_strlen(node_content);
	token_list_add_back(token_list, new_node);
	return (0);
}

/*
this function is supposed to split the input string into tokens and return a list of those tokens
tokens = categorized (word, pipe, redir) constituents of the original string
--> enables parser and later executor to work with categorized user input instead of having to intepret everything --> later processes will know what to do with input snippets based on assigned categories
*/
t_token_list	*lexer(char *input)
{
	int				i;
	t_token_list	*token_list;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		// skip whitespaces
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		// catch redirs
		if (input[i] == '<' || input[i] == '>')
		// this helper function populates token_list and increments i
		{
			if (handle_token_redir(input, &token_list, &i) == -1)
				// TODO: CLEANUP NECESSARY HERE OR IN MAIN FT! (GC?)
				return (NULL);
		}
		// catch pipes
		else if (input[i] == '|')
		{
			// this helper function populates token_list and increments i
			if (handle_token_pipe(&token_list, &i) == -1)
				// TODO: CLEANUP NECESSARY HERE OR IN MAIN FT! (GC?)
				return (NULL);
		}
		// catch everything else
		else if (input[i] != '\0')
		{
			// this helper function populates token_list and increments i
			if (handle_token_word(input, &token_list, &i) == -1)
				// TODO: CLEANUP NECESSARY HERE OR IN MAIN FT! (GC?)
				return (NULL);
		}
	}
	return (token_list);
}
