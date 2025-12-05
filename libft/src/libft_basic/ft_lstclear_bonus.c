/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:40:48 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 14:41:58 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;

	while (*lst != NULL)
	{
		lst_tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = lst_tmp;
	}
	*lst = NULL;
}
