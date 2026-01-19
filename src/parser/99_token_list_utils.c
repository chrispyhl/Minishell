/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_token_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:39 by craabe            #+#    #+#             */
/*   Updated: 2026/01/19 12:20:43 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_token_list	*init_token_list(void)
{
	t_token_list	*token_list;

	token_list = ft_malloc(1, sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->size = 0;
	return (token_list);
}

t_token_node	*create_token_node(char *content, t_token_type type)
{
	t_token_node	*node;

	/*
	malloc: calculates the total bytes needed for your 4 fields:
	pointer *token, enum type, pointer *next, pointer *prev.
	*/
	node = (t_token_node *)ft_malloc(1, sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->token = content;
	node->token_type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	token_list_add_back(t_token_list *list, t_token_node *new_node)
{
	if (list == NULL || new_node == NULL)
		return ;
	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		new_node->prev = list->tail;
		list->tail = new_node;
	}
	list->size++;
}
