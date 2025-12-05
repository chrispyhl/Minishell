/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:49:00 by craabe            #+#    #+#             */
/*   Updated: 2025/07/15 17:36:46 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			dest_len;
	size_t			src_len;
	unsigned int	c;
	size_t			goal_len;

	dest_len = 0;
	src_len = 0;
	c = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	goal_len = dest_len + src_len;
	if (size > dest_len)
	{
		while (src[c] != '\0' && (dest_len < (size - 1)))
			dest[dest_len++] = src[c++];
		dest[dest_len] = '\0';
	}
	else
		return (src_len + size);
	return (goal_len);
}
