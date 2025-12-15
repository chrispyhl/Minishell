
#include "../../includes/parser.h"

t_token_list	*create_token_node(char *content, enum e_token_type type)
{
	t_token_list	*node;

	/*
	malloc: calculates the total bytes needed for your 4 fields:
	pointer *token, enum type, pointer *next, pointer *prev.
	*/
	node = (t_token_list *)malloc(sizeof(t_token_list));
	if (!node)
		return (NULL);
	node->token = content;
	node->token_type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
void	token_list_add_back(t_token_list **head, t_token_list *new_node)
{
	t_token_list	*current;

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

void	free_token_list(t_token_list *token_list)
{
	t_token_list	*temp;

	if (!token_list)
		return ;
	while (token_list)
	{
		temp = token_list->next;
		if (token_list->token)
			free(token_list->token);
		free(token_list);
		token_list = temp;
	}
}
