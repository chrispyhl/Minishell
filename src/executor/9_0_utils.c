/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:10 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/06 10:25:43 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	update_env_if_exists(t_env_list *env, char *key, char *value)
{
	t_env_node	*curr;

	curr = env->head;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (value != NULL)
				curr->value = value;
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	process_export_arg(t_env_list *env, char *arg)
{
	char	*key;
	char	*value;
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		key = ft_malloc(equals - arg + 1, 1);
		ft_strlcpy(key, arg, equals - arg + 1);
		value = gc_strdup(equals + 1);
	}
	else
	{
		key = gc_strdup(arg);
		value = NULL;
	}
	if (!is_valid_env_key(key))
	{
		ft_putstr_fd("chrispyshell: export: invalid identifier\n", 2);
		return (1);
	}
	if (!update_env_if_exists(env, key, value))
		env_add_back(env, key, value);
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	err_msg(char *cmd, char *msg, int status)
{
	ft_putstr_fd("chrispyshell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
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
