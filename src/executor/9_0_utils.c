/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:10 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/12 15:41:54 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	update_env_if_exists(t_env_list *env, char *key, char *value)
{
	t_env_node	*curr;

	curr = env->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (value)
			{
				if (curr->value)
					free (curr->value);
				curr->value = ft_strdup(value);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static void	free_temp_export(char *key, char *value)
{
	if (key)
		free (key);
	if (value)
		free (value);
}

int	process_export_arg(t_env_list *env, char *arg)
{
	char	*key;
	char	*value;
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		key = ft_substr(arg, 0, equals - arg);
		value = ft_strdup(equals + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!is_valid_env_key(key))
	{
		free_temp_export(key, value);
		return (err_msg("not a valid identifier", 1));
	}
	if (!update_env_if_exists(env, key, value))
		env_add_back(env, key, value);
	free_temp_export(key, value);
	return (0);
}

int	err_msg(char *msg, int status)
{
	ft_putstr_fd("chrispyshell: ", 2);
	ft_putendl_fd(msg, 2);
	return (status);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
