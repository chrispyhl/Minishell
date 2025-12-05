/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:06:30 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 18:59:08 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*malloced;
	size_t			i;

	i = 0;
	malloced = malloc(nmemb * size);
	if (!malloced)
		return (NULL);
	while (i < (nmemb * size))
	{
		malloced[i] = 0;
		i++;
	}
	return ((void *)malloced);
}
