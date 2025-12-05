/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:25:27 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 15:57:05 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocation(int n, int digits)
{
	char	*result;

	if (n < 0)
		result = ft_calloc((digits + 2), sizeof(char));
	else
		result = ft_calloc((digits + 1), sizeof(char));
	if (!result)
		return (NULL);
	return (result);
}

static char	*ft_edge_case(int n, int digits)
{
	char	*result;

	if (n == INT_MIN)
	{
		result = malloc(12 * sizeof(char));
		if (!result)
			return (NULL);
		ft_strlcpy(result, "-2147483648", 12);
		return (result);
	}
	if (n == 0)
	{
		result = malloc(2 * sizeof(char));
		if (!result)
			return (NULL);
		ft_strlcpy(result, "0", 2);
		return (result);
	}
	result = ft_allocation(n, digits);
	return (result);
}

static int	ft_digits(int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*result;

	i = ft_digits(n);
	result = ft_edge_case(n, i);
	if (!result)
		return (NULL);
	if ((ft_strncmp(result, "0", 2) == 0) || (ft_strncmp(result, "-2147483648",
				12) == 0))
		return (result);
	if (n < 0)
	{
		n *= -1;
		result[0] = '-';
		i++;
	}
	while (n > 0)
	{
		i--;
		result[i] = ((n % 10) + 48);
		n /= 10;
	}
	return (result);
}
