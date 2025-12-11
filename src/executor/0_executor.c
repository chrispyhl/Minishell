/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/11 18:10:55 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	execute_command_list(t_cmd_list *list)
{
	if (!list || !list->head)
		return (EXIT_SUCCESS); // empty list
	if (list->size < 1)
		return (1); // no list
	if (list->size == 1)
		return (handle_single_cmd(list->head));
	// else
	// 	return (handle_piped_cmd(list));
	return (0);
}
