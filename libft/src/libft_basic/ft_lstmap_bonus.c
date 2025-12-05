/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:40:53 by craabe            #+#    #+#             */
/*   Updated: 2025/07/21 15:43:00 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*lst_entry;
	void	*new_content;

	result = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		lst_entry = ft_lstnew(new_content);
		if (!lst_entry)
		{
			del(new_content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, lst_entry);
		lst = lst->next;
	}
	return (result);
}
