/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:49:53 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/30 15:31:39 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static size_t	word_count(const char *s, char c)
{
	size_t	counter;
	size_t	words;
	size_t	in_word;

	counter = 0;
	words = 0;
	in_word = 0;
	while (s[counter])
	{
		if (s[counter] != c && !in_word)
		{
			words++;
			in_word = 1;
		}
		if (s[counter] == c)
			in_word = 0;
		counter ++;
	}
	return (words);
}

static char	*create_word(const char *s, size_t start, size_t len)
{
	size_t	j;
	char	*temp;

	j = 0;
	temp = ft_malloc(len + 1, 1);
	if (!temp)
		return (NULL);
	while (j < len)
	{
		temp[j] = s[j + start];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

static int	extract_words(const char *s, char c, char **god)
{
	size_t	counter;
	size_t	i;
	size_t	start;

	counter = 0;
	i = 0;
	while (s[counter] != '\0')
	{
		while (s[counter] == c)
			counter++;
		if (s[counter] == '\0')
			break ;
		start = counter;
		while (s[counter] != c && s[counter] != '\0')
			counter++;
		god[i] = create_word(s, start, counter - start);
		if (!god[i])
			return (0);
		i++;
	}
	god[i] = NULL;
	return (1);
}

char	**gc_split(char const *s, char c)
{
	char	**god_array;
	size_t	words;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	god_array = ft_malloc(sizeof(char *) * (words + 1), 1);
	if (!god_array)
		return (NULL);
	if (!extract_words(s, c, god_array))
		return (NULL);
	return (god_array);
}
