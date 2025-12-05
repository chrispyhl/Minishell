/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:37:24 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 15:50:51 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	pos_neg;
	int	result;

	c = 0;
	pos_neg = 1;
	result = 0;
	while (ft_isspace(str[c]) == 1)
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			pos_neg = -1;
		c++;
	}
	if (!(str[c] >= '0' && str[c] <= '9'))
		return (0);
	while (str[c] != '\0' && (str[c] >= '0' && str[c] <= '9'))
	{
		result = result * 10 + (str[c] - '0');
		c++;
	}
	if (pos_neg == -1)
		result *= -1;
	return (result);
}
