/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_more_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:14:29 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 21:17:15 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

int	handle_env(t_env_list *env)
{
	t_env_node	*current;

	if (!env || !env->head)
		return (0);
	current = env->head;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
	return (0);
}

int	handle_exit(t_cmd_node *node)
{
	int	num;

	ft_putstr_fd("exit\n", 2);
	if (node->cmd[1] == NULL)
	{
		gc_free();
		exit(0);
	}
	else if (is_numeric(node->cmd[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: non number arg\n", 2);
		gc_free();
		exit (255);
	}
	else if (node->cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many exit args\n", 2);
		return (1);
	}
	else
	{
		num = ft_atoi(node->cmd[1]);
		gc_free();
		exit(num % 256);
	}
}
