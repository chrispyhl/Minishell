/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_1_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:19:57 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/20 15:38:09 by cpohl            ###   ########.fr       */
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

void	full_cleanup(t_env_list *env)
{
	free_env_list(env);
	gc_free();
}
