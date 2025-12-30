/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:56 by craabe            #+#    #+#             */
/*   Updated: 2025/12/30 13:19:59 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		// TODO: free files list when implemented + use gc
		free(current);
		// TODO: implement gc
		current = next_curr;
	}
	free(cmd_list);
	// TODO: implement gc
}
