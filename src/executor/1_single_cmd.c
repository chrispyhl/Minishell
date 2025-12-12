/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_single_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:52:49 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 21:58:21 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

// int	execute_external(t_cmd_node *node, t_env_list *env)
// {

// }

int	execute_builtin(t_cmd_node *node, t_env_list *env)
{
	 if (ft_strncmp(*node->cmd, "cd", 3) == 0)
	 	return (handle_cd(node, env));
	if (ft_strncmp(*node->cmd, "echo", 5) == 0)
		return (handle_echo(node));
	if (ft_strncmp(*node->cmd, "pwd", 4) == 0)
		handle_pwd();
	 if (ft_strncmp(*node->cmd, "export", 7) == 0)
	 	return (handle_export(node, env));
	 if (ft_strncmp(*node->cmd, "unset", 6) == 0)
	 	return (handle_unset(node, env));
	 if (ft_strncmp(*node->cmd, "env", 4) == 0)
	 	return (handle_env(env));
	 if (ft_strncmp(*node->cmd, "exit", 5) == 0)
	 	return (handle_exit(node));
	return (1);
}

int	handle_single_cmd(t_cmd_node *node, t_env_list *env)
{
	if (node->cmd_type == BUILTIN)
		return (execute_builtin(node, env));
	// if (node->cmd_type == EXTERNAL)
	// 	return (execute_external(node));
	return (0);
}
