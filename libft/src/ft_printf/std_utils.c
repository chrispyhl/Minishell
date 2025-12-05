/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:34:52 by craabe            #+#    #+#             */
/*   Updated: 2025/09/13 17:13:09 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_allocation_uns(int digits)
{
	char	*result;

	result = ft_calloc((digits + 1), sizeof(char));
	if (!result)
		return (NULL);
	return (result);
}

static int	ft_digits_uns(unsigned int n)
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

static char	*ft_itoa_uns(unsigned int n)
{
	int		i;
	char	*result;

	i = ft_digits_uns(n);
	if (n == 0)
	{
		result = malloc(2 * sizeof(char));
		if (!result)
			return (NULL);
		ft_strlcpy(result, "0", 2);
	}
	result = ft_allocation_uns(i);
	if (!result)
		return (NULL);
	while (n > 0)
	{
		i--;
		result[i] = ((n % 10) + 48);
		n /= 10;
	}
	return (result);
}

int	ft_putnbr_fd_uns(unsigned int n, int fd)
{
	char	*nbr;
	int		i;

	nbr = NULL;
	if (n == 0)
	{
		if (write(fd, "0", 1) == -1)
			return (-1);
		return (0);
	}
	nbr = ft_itoa_uns(n);
	if (!nbr)
		return (-1);
	i = 0;
	while (nbr[i] != '\0')
	{
		if (write(fd, &nbr[i], 1) == -1)
		{
			free(nbr);
			return (-1);
		}
		i++;
	}
	free(nbr);
	return (0);
}
