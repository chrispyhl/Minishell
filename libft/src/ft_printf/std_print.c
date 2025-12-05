/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_std_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:39:44 by craabe            #+#    #+#             */
/*   Updated: 2025/09/11 10:15:04 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_char(int arg)
{
	if (ft_putchar_fd(arg, 1) == -1)
		return (-1);
	return (1);
}

ssize_t	ft_print_str(char *arg)
{
	if (arg == NULL)
	{
		if (OS == 2 || OS == 3)
		{
			if (ft_putstr_fd("(null)", 1) == -1)
				return (-1);
			return (6);
		}
		else if (OS == 1 || OS == 0)
		{
			if (ft_putstr_fd("(unknown)", 1) == -1)
				return (-1);
			return (9);
		}
	}
	if (ft_putstr_fd(arg, 1) == -1)
		return (-1);
	return (ft_strlen(arg));
}

ssize_t	ft_print_int(int arg)
{
	ssize_t	digits;

	digits = 0;
	if (ft_putnbr_fd(arg, 1) == -1)
		return (-1);
	if (arg < 0 || arg == 0)
		digits++;
	while (arg != 0)
	{
		arg /= 10;
		digits++;
	}
	return (digits);
}

ssize_t	ft_print_uns_int(unsigned int arg)
{
	ssize_t	digits;

	if (ft_putnbr_fd_uns(arg, 1) == -1)
		return (-1);
	digits = 0;
	if (arg == 0)
		return (1);
	while (arg != 0)
	{
		arg /= 10;
		digits++;
	}
	return (digits);
}
