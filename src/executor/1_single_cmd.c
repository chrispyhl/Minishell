/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_single_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:52:49 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/11 14:35:13 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_buildin()
{
	
}

int	execute_external()
{

}

int	handle_single_cmd(t_cmd_node *node)
{
	if (node->cmd_type == BUILDIN)
		return (execute_buildin(node));
	if (node->cmd_type == EXTERNAL)
		return (execute_external(node));
}
