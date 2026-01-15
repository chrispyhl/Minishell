/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:34 by craabe            #+#    #+#             */
/*   Updated: 2026/01/13 15:56:52 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmd_list	*parser(char *input, t_env_list *env_list)
{
	t_cmd_list		*cmd_list;
	t_token_list	*token_list;

	cmd_list = NULL;
	token_list = lexer(input);
	if (!token_list)
		return (NULL);
	if (check_token_syntax(token_list) != 1)
		// != 1 means either an error (-1) or invalid syntax (0)
		return (NULL);
	if (expander(token_list, env_list) == -1)
		return (NULL);
	cmd_list = create_cmd_list(token_list);
	return (cmd_list); // if create_cmd_list failed, this returns NULL anyway
}
