/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:49 by craabe            #+#    #+#             */
/*   Updated: 2026/01/20 15:51:02 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long long	ft_atoll(const char *str, int *error)
{
	int					c;
	int					pos_neg;
	unsigned long long	result;

	c = 0;
	pos_neg = 1;
	result = 0;
	while (str[c] && (str[c] == 32 || (str[c] >= 9 && str[c] <= 13)))
		c++;
	if ((str[c] == '+' || str[c] == '-') && str[c++] == '-')
		pos_neg = -1;
	if (!(str[c] >= '0' && str[c] <= '9'))
		return (*error = 1, 0);
	while (str[c] >= '0' && str[c] <= '9')
	{
		if (result > __LONG_LONG_MAX__ / 10 || (result == __LONG_LONG_MAX__ / 10
				&& (unsigned long long)(str[c] - '0') > 7 + (pos_neg == -1)))
			return (*error = 1, 0);
		result = result * 10 + (str[c++] - '0');
	}
	while (str[c] && (str[c] == 32 || (str[c] >= 9 && str[c] <= 13)))
		c++;
	if (str[c])
		*error = 1;
	return (result * pos_neg);
}

void	update_shlvl(t_env_list *env)
{
	char		*current_level;
	char		*new_level_str;
	int			lvl;

	if (!env)
		return ;
	current_level = get_env_value(env, "SHLVL");
	if (!current_level)
	{
		set_env_value(env, "SHLVL", "1");
		return ;
	}
	lvl = ft_atoi(current_level);
	if (lvl < 0)
		lvl = -1;
	new_level_str = ft_itoa(lvl + 1);
	if (!new_level_str)
		return ;
	set_env_value(env, "SHLVL", new_level_str);
	free(new_level_str);
}
