/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:47:22 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/12 14:19:56 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	clean_up(void)
{
	gc_free();
	ft_bzero(get_gc(), sizeof(t_gc_list));
}

t_gc_list	*get_gc(void)
{
	static t_gc_list	gc = {0};

	return (&gc);
}

void	gc_init(void)
{
	t_gc_list	*gc;

	gc = get_gc();
	if (!gc)
		return ;
	gc->head = NULL;
	gc->tail = NULL;
	gc->size = 0;
}

void	gc_add(void *ptr)
{
	t_gc_list	*gc;
	t_gc_node	*new_node;

	gc = get_gc();
	if (!gc || !ptr)
		return ;
	new_node = ft_calloc(1, sizeof(t_gc_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	if (gc->head == NULL)
	{
		new_node->next = NULL;
		gc->head = new_node;
		gc->tail = new_node;
	}
	else
	{
		new_node->next = gc->head;
		gc->head = new_node;
	}
	gc->size++;
}

void	gc_free(void)
{
	t_gc_list	*gc;
	t_gc_node	*current;
	t_gc_node	*tmp;

	gc = get_gc();
	if (!gc)
		return ;
	current = gc->head;
	while (current != NULL)
	{
		tmp = current->next;
		free(current->ptr);
		free(current);
		current = tmp;
	}
	gc->head = NULL;
	gc->tail = NULL;
	gc->size = 0;
}
