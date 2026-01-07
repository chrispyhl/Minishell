
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
		current = current->next;
	}
	return (0);
}
