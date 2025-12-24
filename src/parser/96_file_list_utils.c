
#include "../../includes/parser.h"

t_file_list	*init_file_list(void)
{
	t_file_list	*file_list;

	// TODO: gc implementation!
	file_list = malloc(sizeof(t_file_list));
	if (!file_list)
		return (NULL);
	file_list->head = NULL;
	file_list->tail = NULL;
	file_list->size = 0;
	return (file_list);
}

t_file_node	*create_file_node(char *filename, t_redir_type redir_type)
{
	t_file_node	*node;

	node = malloc(sizeof(t_file_node));
	if (!node)
		return (NULL);
	// copy instead of assignment so that filename can be freed while this stays
	node->filename = ft_strdup(filename);
	if (!node->filename)
	{
		free(node);
		return (NULL);
	}
	node->redir_type = redir_type;
	node->next = NULL;
	return (node);
}

void	file_list_add_back(t_file_list *file_list, t_file_node *file_node)
{
	if (!file_list || !file_node)
		return ;
	if (!(file_list)->head)
	{
		file_list->head = file_node;
		file_list->tail = file_node;
	}
	else
	{
		// add new_node to chain, targeting old tail
		file_list->tail->next = file_node;
		// new_node = new tail
		file_list->tail = file_node;
	}
	file_list->size++;
}
