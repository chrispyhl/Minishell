
#include "../../includes/parser.h"

t_token_node	*create_token_node(char *content, enum e_token_type type)
{
	t_token_node	*node;

	/*
	malloc: calculates the total bytes needed for your 4 fields:
	pointer *token, enum type, pointer *next, pointer *prev.
	*/
	node = (t_token_node *)malloc(sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->token = content;
	node->token_type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
void	token_node_add_back(t_token_node **head, t_token_node *new_node)
{
	t_token_node	*current;

	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}

void	free_token_node(t_token_node *token_node)
{
	t_token_node	*temp;

	if (!token_node)
		return ;
	while (token_node)
	{
		temp = token_node->next;
		if (token_node->token)
			free(token_node->token);
		free(token_node);
		token_node = temp;
	}
}
