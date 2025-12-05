/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:30:40 by craabe            #+#    #+#             */
/*   Updated: 2025/08/11 12:02:30 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*result;
	size_t	i;
	size_t	j;
	size_t	str_len;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = (int)start;
	j = 0;
	str_len = ft_strlen(str);
	if (i > str_len)
		return (ft_strdup(""));
	str_len = ft_strlen(s + i);
	if (len > str_len)
		len = str_len;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (j < len && str[i] != '\0')
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
}
