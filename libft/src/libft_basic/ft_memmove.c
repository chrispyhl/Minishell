/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:26:06 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 16:03:56 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_mem_mover(unsigned char *dst, unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst > src)
	{
		while (n > 0)
		{
			dst[n - 1] = src[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			dst[i] = src[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;

	if (dst == (void *) NULL && src == NULL)
		return ((void *) NULL);
	dst_copy = (unsigned char *)dst;
	src_copy = (unsigned char *)src;
	ft_mem_mover(dst_copy, src_copy, n);
	return (dst);
}
