/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:41:28 by craabe            #+#    #+#             */
/*   Updated: 2025/07/15 16:25:26 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				result;
	unsigned int	c;

	result = 0;
	c = 0;
	while ((s1[c] != '\0' || s2[c] != '\0') && c < n)
	{
		if (s1[c] == s2[c])
			c++;
		else
		{
			result = (unsigned char)s1[c] - (unsigned char)s2[c];
			return (result);
		}
	}
	return (result);
}
