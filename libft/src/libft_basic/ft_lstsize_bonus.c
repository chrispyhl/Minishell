/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:40:56 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 16:12:32 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*lst_cpy;

	counter = 0;
	lst_cpy = lst;
	while (lst_cpy)
	{
		lst_cpy = lst_cpy->next;
		counter++;
	}
	return (counter);
}
