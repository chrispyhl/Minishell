/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:19 by craabe            #+#    #+#             */
/*   Updated: 2026/01/13 12:08:28 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_cmd_node	*populate_cmd_node(t_token_node *current)
{
	t_cmd_node	*cmd_node;
	char		**cmd_array;

	cmd_node = ft_malloc(1, sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->files = init_file_list();
	if (!cmd_node->files)
		return (NULL);
	if (extract_redirs(current, cmd_node) == -1)
		return (NULL);
	cmd_array = tokens_to_array(current);
	if (!cmd_array)
		return (NULL);
	cmd_node->cmd = cmd_array;
	cmd_node->cmd_type = set_cmd_type(cmd_array[0]);
	cmd_node->next = NULL;
	return (cmd_node);
}

static void	populate_cmd_list(t_cmd_list *cmd_list, t_cmd_node *cmd_node)
{
	if (!cmd_list->head)
	{
		cmd_list->head = cmd_node;
		cmd_list->tail = cmd_node;
	}
	else
	{
		cmd_list->tail->next = cmd_node;
		cmd_list->tail = cmd_node;
	}
	cmd_list->size++;
}

t_cmd_list	*create_cmd_list(t_token_list *token_list)
{
	t_cmd_list		*cmd_list;
	t_cmd_node		*cmd_node;
	t_token_node	*current;

	current = token_list->head;
	cmd_list = ft_malloc(1, sizeof(t_cmd_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	while (current)
	{
		cmd_node = populate_cmd_node(current);
		if (!cmd_node)
			return (NULL);
		populate_cmd_list(cmd_list, cmd_node);
		while (current && current->token_type != T_PIPE)
			current = current->next;
		if (current && current->token_type == T_PIPE)
			current = current->next;
	}
	return (cmd_list);
}
