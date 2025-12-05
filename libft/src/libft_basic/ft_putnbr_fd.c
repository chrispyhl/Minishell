/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:25:47 by craabe            #+#    #+#             */
/*   Updated: 2025/09/11 10:13:26 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_fd_edge(int n, int fd)
{
	if (n == 0)
	{
		if (write(fd, "0", 1) == -1)
			return (-1);
	}
	if (n == INT_MIN)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return (-1);
	}
	return (0);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	*nbr;
	int		i;

	nbr = NULL;
	if (n == 0 || n == INT_MIN)
		return (ft_putnbr_fd_edge(n, fd));
	nbr = ft_itoa(n);
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
