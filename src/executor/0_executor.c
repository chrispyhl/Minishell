/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:30:50 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/24 13:31:46 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	execute_command_list(t_cmd_list *list, t_env_list *env)
{
	if (!list || !list->head)
		return (EXIT_SUCCESS); // empty list
	if (list->size < 1)
		return (1); // no list
	if (list->size == 1)
		return (handle_single_cmd(list->head, env));
	 else
	 	return (handle_piped_cmd(list, env));
	return (0);
}
