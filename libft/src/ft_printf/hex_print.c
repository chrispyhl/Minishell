/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:39:48 by craabe            #+#    #+#             */
/*   Updated: 2025/09/11 10:00:24 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_upper_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

ssize_t	ft_print_pt(void *arg)
{
	char			*str;
	unsigned long	pt_long;

	if (!arg || arg == 0)
	{
		if (OS == 3)
		{
			if (ft_putstr_fd("(nil)", 1) == -1)
				return (-1);
			return (5);
		}
		if (ft_putstr_fd("0x0", 1) == -1)
			return (-1);
		return (3);
	}
	if (ft_putstr_fd("0x", 1) == -1)
		return (-1);
	pt_long = (unsigned long)arg;
	str = ft_long_hex(pt_long);
	if (ft_putstr_fd(str, 1) == -1)
		return (-1);
	return (ft_strlen(str) + 2);
}

ssize_t	ft_print_hex(unsigned int arg, int mode)
{
	char	*str;

	if (arg == 0)
	{
		if (ft_putchar_fd('0', 1) == -1)
			return (-1);
		return (1);
	}
	if (mode == 1)
		str = ft_upper_string(ft_int_hex(arg));
	else
		str = ft_int_hex(arg);
	if (ft_putstr_fd(str, 1) == -1)
		return (-1);
	return (ft_strlen(str));
}
