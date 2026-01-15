
#include "../../includes/parser.h"

// reminder: return (token_type - 2) would work and make this ft a one-liner
// BUT it makes maintenance harder should we add other members to enums later
t_redir_type	token_type_to_redir_type(t_token_type token_type)
{
	if (token_type == T_REDIR_IN)
		return (NODE_INPUT);
	else if (token_type == T_REDIR_OUT)
		return (NODE_OUTPUT);
	else if (token_type == T_REDIR_APP)
		return (NODE_APPEND);
	else if (token_type == T_HEREDOC)
		return (NODE_HEREDOC);
	else
		return (-1);
}

int	extract_redirs(t_token_node *current, t_cmd_node *cmd_node)
{
	t_file_node	*new_node;

	while (current && current->token_type != T_PIPE)
	{
		// note: >= T_REDIR_IN would soffice,
		// but including end is better practice for maintenance
		if (current->token_type >= T_REDIR_IN
			&& current->token_type <= T_HEREDOC)
		{
			if (!current->next)
				return (-1);
			// file_name = current->next->token since this is the normal syntax
			// for example: > result.txt
			new_node = create_file_node(current->next->token,
					token_type_to_redir_type(current->token_type));
			if (!new_node)
				return (-1);
			file_list_add_back(cmd_node->files, new_node);
			// advance node; next node (file_name) will be skipped at loop end
			current = current->next;
		}
		if (current)
			current = current->next;
	}
	return (0);
}

int	populate_array(t_token_node *token_node, char **cmd_array)
{
	int				i;
	t_token_node	*current;

	i = 0;
	current = token_node;
	while (current && current->token_type != T_PIPE)
	{
		if (current->token_type >= T_REDIR_IN
			&& current->token_type <= T_HEREDOC)
		{
			if (current->next)
				current = current->next;
		}
		else
		{
			cmd_array[i] = gc_strdup(current->token);
			if (!cmd_array[i])
				return (-1);
			i++;
		}
		if (current)
			current = current->next;
	}
	cmd_array[i] = NULL;
	return (0);
}

char	**tokens_to_array(t_token_node *token_node)
{
	t_token_node	*current;
	ssize_t			node_nbr;
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
	cmd_array = ft_malloc(node_nbr + 1, sizeof(char *));
	// +1 for the pt to NULL
	if (!cmd_array)
		return (NULL);
	if (populate_array(token_node, cmd_array) == -1)
		return (NULL);
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
