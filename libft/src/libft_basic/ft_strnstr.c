/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:10:17 by craabe            #+#    #+#             */
/*   Updated: 2025/07/18 18:20:17 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			c = 0;
			while (haystack[i + c] == needle[c] && haystack[i + c] != '\0' && (i
					+ c) <= len)
				c++;
			if (needle[c] == '\0' && (i + c) <= len)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
