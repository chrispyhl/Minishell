/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_handle_more_builtins.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:14:29 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/12 15:09:54 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

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
	long long	status;
	int			error;

	error = 0;
	if (!node->cmd[1])
	{
		gc_free();
		exit(0);
	}
	status = ft_atoll(node->cmd[1], &error);
	if (error || !is_numeric(node->cmd[1]))
	{
		err_msg("numeric argument required", 2);
		gc_free();
		exit (2);
	}
	if (node->cmd[2])
		return (err_msg("too many arguments", 1));
	gc_free();
	exit((unsigned char)status);
}

int	handle_unset(t_cmd_node *node, t_env_list *env)
{
	int	i;

	if (!node->cmd[1])
		return (0);
	i = 1;
	while (node->cmd[i])
	{
		remove_env_node(env, node->cmd[i]);
		i++;
	}
	return (0);
}

int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, 1);
		free (cwd);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("getcwd failed to get working directory\n", 2);
	return (0);
}
