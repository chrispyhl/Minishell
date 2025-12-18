

#include "../../includes/minishell.h"

void	free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_node	*current;
	t_cmd_node	*next_curr;

	if (!cmd_list)
		return ;
	current = cmd_list->head;
	while (current)
	{
		next_curr = current->next;
		if (current->cmd)
			free_array(current->cmd);
		// TODO: free files list when implemented + use gc
		free(current);
		// TODO: implement gc
		current = next_curr;
	}
	free(cmd_list);
	// TODO: implement gc
}
