/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:38:59 by craabe            #+#    #+#             */
/*   Updated: 2025/07/15 16:10:36 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	to_find;
	unsigned int	i;
	int				found;
	char			*result;

	to_find = (char)c;
	i = 0;
	found = -1;
	result = (char *)str;
	while (result[i] != '\0')
	{
		if (result[i] == to_find)
			found = i;
		i++;
	}
	if (result[i] == to_find)
		return (&result[i]);
	if (found != -1)
		return (&result[found]);
	return (0);
}
