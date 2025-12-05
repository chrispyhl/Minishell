/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:24:06 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 17:16:28 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_str_counter(char *s, char c)
{
	unsigned int	i;
	int				str_c;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	str_c = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i] != c && s[i - 1] == c))
			str_c++;
		i++;
	}
	return (str_c);
}

static char	**ft_malloc_free(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (NULL);
}

static int	ft_edge_case(char **result, char *s, char c, int str_nbr)
{
	if (s[0] == '\0')
	{
		result[0] = NULL;
		return (1);
	}
	else if (ft_strchr(s, c) == NULL)
	{
		result[0] = ft_strdup(s);
		if (!result[0])
		{
			free(result);
			return (-1);
		}
		result[1] = NULL;
		return (1);
	}
	else if (str_nbr == 0)
	{
		result[0] = NULL;
		return (1);
	}
	return (0);
}

static int	ft_str_to_result(char **result, char *s, int str_nbr, char c)
{
	int				i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	k = 0;
	while (i < str_nbr)
	{
		while (s[k] == c)
			k++;
		if (ft_strchr(s + k, c) == NULL)
			result[i] = malloc((ft_strlen(s + k) + 1) * sizeof(char));
		else
			result[i] = malloc((ft_strchr(s + k, c) - (s + k) + 1)
					* sizeof(char));
		if (!result[i])
			return (ft_malloc_free(result, i), -1);
		j = 0;
		while (s[k] != c && s[k] != '\0')
			result[i][j++] = s[k++];
		result[i++][j] = '\0';
	}
	result[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		str_nbr;
	int		edge_case_check;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	str_nbr = ft_str_counter(str, c);
	result = malloc((str_nbr + 1) * sizeof(char *));
	if (!result)
	{
		ft_malloc_free(result, -1);
		return (NULL);
	}
	edge_case_check = ft_edge_case(result, str, c, str_nbr);
	if (edge_case_check == -1)
		return (NULL);
	if (edge_case_check == 1)
		return (result);
	if (ft_str_to_result(result, str, str_nbr, c) == -1)
		return (NULL);
	return (result);
}
