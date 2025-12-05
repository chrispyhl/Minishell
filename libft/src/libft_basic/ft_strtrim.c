/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:05:13 by craabe            #+#    #+#             */
/*   Updated: 2025/07/18 18:25:28 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_start(char *str, char *set)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] != '\0' && ft_strchr(set, str[i]) != NULL)
		i++;
	result = &str[i];
	return (result);
}

static char	*ft_get_end(char *str, char *set)
{
	char	*result;
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_strchr(set, str[i]) != NULL)
		i--;
	result = &str[i + 1];
	return (result);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	char	*start_pt;
	char	*end_pt;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start_pt = ft_get_start((char *)s1, (char *)set);
	end_pt = ft_get_end((char *)s1, (char *)set);
	if (start_pt > end_pt || start_pt[0] == '\0')
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	result = malloc((end_pt - start_pt + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, start_pt, (end_pt - start_pt + 1));
	return (result);
}
