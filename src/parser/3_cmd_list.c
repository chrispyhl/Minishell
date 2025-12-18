
#include "../../includes/parser.h"

static char	**tokens_to_array(t_token_list *token_list)
{
	t_token_list	*current;
	ssize_t			node_nbr;
	int				i;
	char			**cmds;

	current = token_list;
	node_nbr = 0;
	while (current && current->token_type != T_PIPE)
	{
		node_nbr++;
		current = current->next;
	}
	cmds = malloc((node_nbr + 1) * sizeof(char *)); // +1 for the pt to NULL
	i = 0;
	if (!cmds)
		// TODO: implement gc!
		return (NULL);
	current = token_list;
	while (current && current->token_type != T_PIPE)
	{
		cmds[i] = ft_strdup(current->token);
		if (!cmds[i])
		{
			free_array(cmds);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

// TODO: does not handle redirs/heredoc and files etc. yet
// TODO: gc implementation!
t_cmd_list	*create_cmd_list(t_token_list *token_list)
{
	char			**cmds;
	t_cmd_list		*cmd_list;
	t_cmd_node		*cmd_node;
	t_token_list	*current;

	current = token_list;
	cmd_list = malloc(sizeof(t_cmd_list));
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
	while (current)
	{
		cmds = tokens_to_array(current);
		if (!cmds)
		{
			free_cmd_list(cmd_list);
			return (NULL);
		}
		cmd_node = malloc(sizeof(t_cmd_node));
		if (!cmd_node)
		{
			free_array(cmds);
			free_cmd_list(cmd_list);
			return (NULL);
		}
		cmd_node->cmd_type = UNDEF;
		cmd_node->cmd = cmds;
		cmd_node->next = NULL;
		cmd_node->files = NULL;
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
