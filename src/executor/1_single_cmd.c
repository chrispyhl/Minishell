/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_single_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:52:49 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/11 18:13:51 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

// int	execute_external()
// {

// }

int	execute_builtin(t_cmd_node *node)
{
	// if (ft_strncmp(node->cmd, "cd", 3) == 0)
	// 	return (handle_cd(node));
	// if (ft_strncmp(node->cmd, "echo", 5) == 0)
	// 	return (handle_echo(node));
	if (ft_strncmp(*node->cmd, "pwd", 4) == 0)
		handle_pwd();
	// if (ft_strncmp(node->cmd, "export", 7) == 0)
	// 	return (handle_export(node));
	// if (ft_strncmp(node->cmd, "unset", 6) == 0)
	// 	return (handle_unset(node));
	// if (ft_strncmp(node->cmd, "env", 4) == 0)
	// 	return (handle_env(node));
	// if (ft_strncmp(node->cmd, "exit", 5) == 0)
	// 	return (handle_exit(node));
	return (1);
}

int	handle_single_cmd(t_cmd_node *node)
{
	if (node->cmd_type == BUILTIN)
		return (execute_builtin(node));
	// if (node->cmd_type == EXTERNAL)
	// 	return (execute_external(node));
	return (0);
}
