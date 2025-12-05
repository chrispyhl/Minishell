/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:16:15 by craabe            #+#    #+#             */
/*   Updated: 2025/07/10 14:30:18 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned int	i;
	unsigned char	insert;
	unsigned char	*str_copy;

	i = 0;
	insert = c;
	str_copy = (unsigned char *)str;
	while (i < len)
	{
		*str_copy = insert;
		str_copy++;
		i++;
	}
	return (str);
}
