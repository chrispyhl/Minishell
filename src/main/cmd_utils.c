/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:56 by craabe            #+#    #+#             */
/*   Updated: 2026/01/02 18:54:02 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_file_list(t_file_list *file_list)
{
	t_file_node	*current;
	t_file_node	*next_node;

	if (!file_list)
		return ;
	current = file_list->head;
	while (current)
	{
		next_node = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next_node;
	}
	free(file_list);
}

void	free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_node	*current;
	t_cmd_node	*next_curr;

	if (!cmd_list)
		return ;
	current = cmd_list->head;
	while (current)
	{
		next_curr = current->next;
		if (current->cmd)
			free_array(current->cmd);
		if (current->files)
			free_file_list(current->files);
		// TODO: use gc!
		free(current);
		// TODO: implement gc
		current = next_curr;
	}
	free(cmd_list);
	// TODO: implement gc
}
