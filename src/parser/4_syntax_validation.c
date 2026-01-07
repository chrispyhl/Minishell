
#include "../../includes/parser.h"

int	check_token_syntax(t_token_list *token_list)
{
	t_token_node	*current;

	current = token_list->head;
	if (current->token_type == T_PIPE)
	{
		ft_printf("chrispyshell: syntax error near unexpected token '|'\n");
		return (0);
	}
	while (current)
	{
		// if the current token is a pipe,
		if (current->token_type == T_PIPE)
		{
			if (!current->next)
			{
				// TODO: IMPORTANTE! clarify if MULTILINE HANDLING is mandatory!
				ft_printf("chrispyshell: syntax error near unexpected token 'newline'\n");
				return (0);
			}
			if (current->next->token_type == T_PIPE)
			{
				ft_printf("chrispyshell: syntax error near unexpected token '|'\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
