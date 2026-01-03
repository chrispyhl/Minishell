/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/03 12:12:13 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	execute_command_list(t_cmd_list *list, t_env_list *env)
{
	t_cmd_node	*current; // TEMP!

	if (!list || !list->head || list->size == 0)
		return (EXIT_SUCCESS); // empty list
	// TEMP!
	current = list->head;
	while (current)
	{
		fix_broken_parser_node(current);
		current = current->next;
	}
	// TEMP!
	if (list->size < 1)
		return (1); // no list
	if (list->size == 1)
		return (handle_single_cmd(list->head, env));
	else
		return (handle_piped_cmd(list, env));
	return (0);
}
