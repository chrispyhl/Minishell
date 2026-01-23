/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_1_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:19:57 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 16:37:18 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

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

void	full_cleanup(t_env_list *env)
{
	free_env_list(env);
	gc_free();
}

void	update_underscore(t_env_list *env, char **cmd)
{
	int			i;

	if (!env || !cmd || !cmd[0])
		return ;
	i = 0;
	while (cmd[i])
		i++;
	set_env_value(env, "_", cmd[i - 1]);
}
