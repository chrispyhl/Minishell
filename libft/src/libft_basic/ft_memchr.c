/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:49:29 by craabe            #+#    #+#             */
/*   Updated: 2025/07/18 17:29:46 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	to_find;
	unsigned char	*result;
	unsigned int	i;

	i = 0;
	to_find = (char)c;
	result = (unsigned char *)s;
	while (i < n)
	{
		if (*result == to_find)
			return ((void *)result);
		result++;
		i++;
	}
	return (NULL);
}
