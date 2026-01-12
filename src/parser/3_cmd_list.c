/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:19 by craabe            #+#    #+#             */
/*   Updated: 2026/01/12 14:02:56 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	**tokens_to_array(t_token_node *token_node)
{
	t_token_node	*current;
	ssize_t			node_nbr;
	int				i;
	char			**cmd_array;

	current = token_node;
	node_nbr = 0;
	while (current && current->token_type != T_PIPE)
	{
		// note: >= T_REDIR_IN would soffice,
		// but including end is better practice for maintenance
		if (current->token_type >= T_REDIR_IN
			&& current->token_type <= T_HEREDOC)
			// skip redir command
			current = current->next;
		else
			// increment!
			node_nbr++;
		// safety check for scenarios like "ls >"
		if (current)
			current = current->next;
	}
	cmd_array = ft_malloc(sizeof(char *), node_nbr + 1);
	// +1 for the pt to NULL
	i = 0;
	if (!cmd_array)
		// TODO: implement gc!
		return (NULL);
	current = token_node;
	while (current && current->token_type != T_PIPE)
	{
		if (current->token_type >= T_REDIR_IN
			&& current->token_type <= T_HEREDOC)
			// skip redir command
			current = current->next;
		else
		{
			cmd_array[i] = gc_strdup(current->token);
			if (!cmd_array[i])
				return (NULL);
			i++;
		}
		if (current)
			current = current->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

t_cmd_type	set_cmd_type(char *cmd)
{
	static const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
			"env", "exit", NULL};
	int					i;
	size_t				cmd_len;

	if (!cmd || cmd[0] == '\0')
		return (EMPTY);
	i = 0;
	cmd_len = ft_strlen(cmd);
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], cmd_len + 1) == 0)
			return (BUILTIN);
		i++;
	}
	return (EXTERNAL);
}

// TODO: gc implementation!
t_cmd_list	*create_cmd_list(t_token_list *token_list)
{
	char			**cmd_array;
	t_cmd_list		*cmd_list;
	t_cmd_node		*cmd_node;
	t_token_node	*current;

	current = token_list->head;
	cmd_list = ft_malloc(sizeof(t_cmd_list), 1);
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	while (current)
	{
		cmd_node = ft_malloc(sizeof(t_cmd_node), 1);
		// TODO: implement gc!
		if (!cmd_node)
			return (NULL);
		cmd_node->files = init_file_list();
		// TODO: implement gc!
		if (!cmd_node->files)
			return (NULL);
		if (extract_redirs(current, cmd_node) == -1)
			return (NULL);
		cmd_array = tokens_to_array(current);
		if (!cmd_array)
			return (NULL);
		cmd_node->cmd = cmd_array;
		cmd_node->cmd_type = set_cmd_type(cmd_array[0]);
		cmd_node->next = NULL;
		if (!cmd_list->head)
		{
			cmd_list->head = cmd_node;
			cmd_list->tail = cmd_node;
		}
		else
		{
			cmd_list->tail->next = cmd_node;
			cmd_list->tail = cmd_node;
		}
		cmd_list->size++;
		while (current && current->token_type != T_PIPE)
			current = current->next;
		if (current && current->token_type == T_PIPE)
			current = current->next;
	}
	return (cmd_list);
}
