
#include "../../includes/parser.h"

static int	handle_token_word(char *input, t_token_list **token_list, int *i)
{
	char			*node_content;
	int				j;
	t_token_list	*new_node;

	char *seg; // seg = segment of the string, starting from index i
	seg = input + *i;
	j = 0;
	// skip until something that does not belong to the word is encountered
	while (seg[j] && seg[j] != '|' && seg[j] != '<' && seg[j] != '>'
		&& seg[j] != ' ' && seg[j] != '\t')
		j++;
	// create a new node containing seg up until the undesired character
	// since ft_substr copies with the condition (i < len), it stops before j
	node_content = ft_substr(seg, 0, j);
	if (!node_content)
		return (-1);
	// this creates a new list node with the substr and it's token category (WORD)
	new_node = create_token_node(node_content, WORD);
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
		{
			// [handle_token_redir function]
			// passing &token_list, input and &i to this helper function
			// this helper function is supposed to populate token_list and increment i
			// this helper function can check if more > or < follow
		}
		// catch pipes
		else if (input[i] == '|')
		{
			// [handle_token_pipe function]
			// passing &token_list, input and &i to this helper function
			// this helper function is supposed to populate token_list and increment i
		}
		// catch everything else
		else if (input[i] != '\0')
		{
			if (handle_token_word(input, &token_list, &i) == -1)
				return (NULL);
			// handle_token_word
			// passing &token_list, input and &i to this helper function
			// this helper function is supposed to populate token_list and increment i
		}
	}
	return (token_list);
}
