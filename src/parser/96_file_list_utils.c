/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   96_file_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:24 by craabe            #+#    #+#             */
/*   Updated: 2026/01/12 13:47:50 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_file_list	*init_file_list(void)
{
	t_file_list	*file_list;

	// TODO: gc implementation!
	file_list = ft_malloc(sizeof(t_file_list), 1);
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

	node = ft_malloc(sizeof(t_file_node), 1);
	if (!node)
		return (NULL);
	// copy instead of assignment so that filename can be freed while this stays
	node->filename = gc_strdup(filename);
	if (!node->filename)
		return (NULL);
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
