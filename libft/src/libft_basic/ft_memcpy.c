/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:06:29 by craabe            #+#    #+#             */
/*   Updated: 2025/07/18 13:31:38 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	unsigned int	i;

	if (dst == (void *)0 && src == (void *)0)
		return ((void *)0);
	dst_copy = (unsigned char *)dst;
	src_copy = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*dst_copy = *src_copy;
		dst_copy++;
		src_copy++;
		i++;
	}
	return (dst);
}
