/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_b_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:30:53 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/27 12:10:01 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	p_e_key_val(char *arg, char **key, char **value, int *append)
{
	char	*equals;

	*append = 0;
	*value = NULL;
	equals = ft_strchr(arg, '=');
	if (equals && equals > arg && *(equals - 1) == '+')
	{
		*append = 1;
		*key = ft_substr(arg, 0, equals - arg - 1);
		*value = ft_strdup(equals + 1);
	}
	else if (equals)
	{
		*key = ft_substr(arg, 0, equals - arg);
		*value = ft_strdup(equals + 1);
	}
	else
		*key = ft_strdup(arg);
}

static int	set_e_val(t_env_list *env, char *key, char *value, int append)
{
	if (append)
	{
		if (append_env_value(env, key, value) == 0)
			set_env_value(env, key, value);
	}
	else
	{
		if (update_env_if_exists(env, key, value) == 0)
			env_add_back(env, key, value);
	}
	return (0);
}

int	process_export_arg(t_env_list *env, char *arg)
{
	char	*key;
	char	*value;
	int		append;

	p_e_key_val(arg, &key, &value, &append);
	if (!is_valid_env_key(key))
	{
		free(key);
		free(value);
		return (err_msg("not a valid identifier", 1));
	}
	set_e_val(env, key, value, append);
	free(key);
	free(value);
	return (0);
}

void	print_export_line(char *line)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (line[i] && line[i] != '=')
		ft_putchar_fd(line[i++], 1);
	if (line[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(&line[i + 1], 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
}
