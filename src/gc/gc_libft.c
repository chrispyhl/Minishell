/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:54:10 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/09 14:28:56 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	counter;
	size_t	s_len;

	counter = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = ft_malloc(len + 1, 1);
	if (!str)
		return (0);
	while (counter < len && s[start + counter] != '\0')
	{
		str[counter] = s[start + counter];
		counter++;
	}
	str[counter] = '\0';
	return (str);
}

char	*gc_strdup(const char *s1)
{
	char	*mem1;
	size_t	s1_length;
	size_t	counter;

	s1_length = ft_strlen(s1);
	mem1 = ft_malloc(s1_length + 1, 1);
	if (!mem1)
		return (NULL);
	counter = 0;
	while (s1[counter])
	{
		mem1[counter] = s1[counter];
		counter++;
	}
	mem1[counter] = '\0';
	return (mem1);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	counter;
	size_t	counter2;

	counter = 0;
	counter2 = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	while (s1[counter] != '\0')
	{
		str[counter] = s1[counter];
		counter++;
	}
	while (s2[counter2] != '\0')
	{
		str[counter] = s2[counter2];
		counter++;
		counter2++;
	}
	str[counter] = '\0';
	return (str);
}
