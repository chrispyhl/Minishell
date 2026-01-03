/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:13:48 by chris             #+#    #+#             */
/*   Updated: 2026/01/02 16:39:17 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:37:24 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 15:50:51 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

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
