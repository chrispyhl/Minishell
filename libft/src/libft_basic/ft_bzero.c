/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:59:22 by craabe            #+#    #+#             */
/*   Updated: 2025/07/10 14:29:55 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*str_copy;
	unsigned int	i;

	i = 0;
	str_copy = (unsigned char *)str;
	if (n != 0)
	{
		while (i < n)
		{
			*str_copy = '\0';
			str_copy++;
			i++;
		}
	}
}
