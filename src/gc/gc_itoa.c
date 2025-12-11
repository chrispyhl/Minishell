/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:57:20 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/11 18:28:05 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"


static unsigned int	handle_neg(int n, char *result)
{
	if (n < 0)
	{
		result[0] = '-';
		return (-n);
	}
	return (n);
}

static char	*handle_zero(int n, char *result)
{
	if (n == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	return (result);
}

static int	ft_digits(int n)
{
	int	digits;

	digits = 0;
	if (n <= 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*gc_itoa(int n)
{
	int				len;
	char			*result;
	unsigned int	num;
	int				counter;

	len = ft_digits(n);
	result = ft_malloc(len + 1, 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		return (handle_zero(n, result));
	num = handle_neg(n, result);
	counter = len - 1;
	while (num > 0)
	{
		result[counter] = (num % 10) + '0';
		num /= 10;
		counter--;
	}
	return (result);
}
