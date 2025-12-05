/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:25:23 by craabe            #+#    #+#             */
/*   Updated: 2025/08/11 11:57:58 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int c)
{
	unsigned char	to_find;
	size_t			i;
	char			*result;

	to_find = (unsigned char)c;
	i = 0;
	result = (char *)str;
	while (result[i] != '\0')
	{
		if (result[i] == to_find)
			return (&result[i]);
		i++;
	}
	if (result[i] == to_find)
		return (&result[i]);
	return (NULL);
}
