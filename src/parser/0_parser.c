/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:34 by craabe            #+#    #+#             */
/*   Updated: 2025/12/09 22:33:39 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_list	*parser(char *input)
{
	t_cmd_list	*cmd_list;

	(void)input;
	cmd_list = NULL;
	// cmd_list->head = NULL;
	// cmd_list->tail = NULL;
	// cmd_list->size = 0;
	ft_putstr_fd("parser called successfully\n", 1);
	return (cmd_list);
}
