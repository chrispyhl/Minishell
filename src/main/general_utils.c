/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:49 by craabe            #+#    #+#             */
/*   Updated: 2026/01/03 13:55:57 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		// TODO: implement gc
		free(array[i]);
		i++;
	}
	// TODO: implement gc
	free(array);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long long	ft_atoll(const char *str, int *error)
{
	int					c;
	int					pos_neg;
	unsigned long long	result;

	c = 0;
	pos_neg = 1;
	result = 0;
	while (ft_isspace(str[c]))
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			pos_neg = -1;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		if (result > __LONG_LONG_MAX__ / 10 || (result == __LONG_LONG_MAX__ / 10
				&& (unsigned long long)(str[c] - '0') > (unsigned long long)
				(__LONG_LONG_MAX__ % 10 + (pos_neg == -1))))
					return (*error = 1, 0);
		result = result * 10 + (str[c++] - '0');
	}
	return (result * pos_neg);
}
