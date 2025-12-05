/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:40:51 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 14:42:31 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_cpy;

	lst_cpy = lst;
	if (lst_cpy == NULL)
		return (NULL);
	while (lst_cpy->next != NULL)
		lst_cpy = lst_cpy->next;
	return (lst_cpy);
}
