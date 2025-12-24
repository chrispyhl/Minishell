/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:34 by craabe            #+#    #+#             */
/*   Updated: 2025/12/24 15:02:54 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmd_list	*parser(char *input, t_env_list *env_list)
{
	t_cmd_list		*cmd_list;
	t_token_node	*token_node;

	(void)input;
	cmd_list = NULL;
	token_node = lexer(input);
	if (!token_node)
		return (NULL); // TODO: additional error handling required
	if (expander(token_node, env_list) == -1)
		return (NULL); // TODO: additional error handling required
	cmd_list = create_cmd_list(token_node);
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}
