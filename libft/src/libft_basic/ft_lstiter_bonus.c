/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:40:50 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 16:08:58 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_tmp;

	lst_tmp = lst;
	while (lst_tmp != NULL)
	{
		lst_tmp = lst->next;
		f(lst->content);
		lst = lst_tmp;
	}
}
