/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:15 by craabe            #+#    #+#             */
/*   Updated: 2026/01/21 12:51:05 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	handle_heredoc_expansion(t_token_node *current, t_env_list *env_list,
		int *heredoc_found)
{
	int	quotes_found;

	quotes_found = 0;
	if (ft_strchr(current->token, '\'') || ft_strchr(current->token, '\"'))
		quotes_found = 1;
	current->heredoc_quote = quotes_found;
	// only expand delimiter if no quotes where found
	if (quotes_found == 0)
		if (handle_expansion(current, env_list) == -1)
			return (-1);
	*heredoc_found = 0;
	return (0);
}

static int	expand_word(t_token_node *current, t_env_list *env_list,
		int *heredoc_found)
{
	if (*heredoc_found == 1)
	{
		if (handle_heredoc_expansion(current, env_list, heredoc_found) == -1)
			return (-1);
	}
	else if (handle_expansion(current, env_list) == -1)
		return (-1);
	if (remove_quotes(current) == -1)
		return (-1);
	return (0);
}

int	expander(t_token_list *token_list, t_env_list *env_list)
{
	t_token_node	*current;
	int				heredoc_found;

	current = token_list->head;
	heredoc_found = 0;
	while (current)
	{
		if (current->token_type == T_HEREDOC)
			heredoc_found = 1;
		else if (current->token_type != T_WORD)
			heredoc_found = 0;
		else if (current->token_type == T_WORD)
			if (expand_word(current, env_list, &heredoc_found) == -1)
				return (-1);
		current = current->next;
	}
	return (0);
}
