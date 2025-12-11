/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:34 by craabe            #+#    #+#             */
/*   Updated: 2025/12/11 17:56:12 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmd_list	*parser(char *input, t_env_list *env_list)
{
	t_cmd_list		*cmd_list;
	t_token_list	*token_list;

	(void)input;
	cmd_list = NULL;
	token_list = lexer(input);
	// call expander with token_list and env_list here!
	ft_putstr_fd("parser called successfully\n", 1);
	return (cmd_list);
}
