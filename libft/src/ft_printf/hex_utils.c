/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_hex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:39:51 by craabe            #+#    #+#             */
/*   Updated: 2025/09/11 09:12:53 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_reversal(char *str)
{
	int		str_len;
	int		i;
	char	temp;

	str_len = ft_strlen(str) - 1;
	i = 0;
	while (i < str_len)
	{
		temp = str[i];
		str[i] = str[str_len];
		str[str_len] = temp;
		i++;
		str_len--;
	}
	return (str);
}

char	*ft_long_hex(unsigned long nbr)
{
	static char		str[17];
	int				i;
	unsigned long	mod;

	i = 0;
	while (nbr != 0)
	{
		mod = nbr % 16;
		if (mod < 10)
			str[i] = mod + 48;
		else
			str[i] = mod + 87;
		nbr /= 16;
		i++;
	}
	str[i] = '\0';
	return (ft_reversal(str));
}

char	*ft_int_hex(unsigned int nbr)
{
	static char	str[9];
	int			i;
	int			mod;

	i = 0;
	while (nbr != 0)
	{
		mod = nbr % 16;
		if (mod < 10)
			str[i] = mod + 48;
		else
			str[i] = mod + 87;
		nbr /= 16;
		i++;
	}
	str[i] = '\0';
	return (ft_reversal(str));
}
