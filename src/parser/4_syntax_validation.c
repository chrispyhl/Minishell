
#include "../../includes/parser.h"

static int	check_pipe(t_token_node *current)
{
	if (!current->next)
	{
		// TODO: IMPORTANTE! clarify if MULTILINE HANDLING is mandatory!
		ft_putstr_fd("chrispyshell: syntax error near unexpected token 'newline'\n",
			2);
		return (0);
	}
	if (current->next->token_type == T_PIPE)
	{
		ft_putstr_fd("chrispyshell: syntax error near unexpected token '|'\n",
			2);
		return (0);
	}
	return (1);
}

static int	check_redir(t_token_node *current)
{
	if (!current->next)
	{
		ft_putstr_fd("chrispyshell: syntax error near unexpected token 'newline'\n",
			2);
		return (0);
	}
	if (current->next->token_type != T_WORD)
	{
		ft_putstr_fd("chrispyshell: syntax error near unexpected token '", 2);
		ft_putstr_fd(current->next->token, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

int	check_token_syntax(t_token_list *token_list)
{
	t_token_node	*current;

	current = token_list->head;
	if (current->token_type == T_PIPE)
	{
		ft_putstr_fd("chrispyshell: syntax error near unexpected token '|'\n", 2);
		return (0);
	}
	while (current)
	{
		// if the current token is a pipe,
		if (current->token_type == T_PIPE)
			if (check_pipe(current) == 0)
				return (0);
		// if the current token is a redir/heredoc
		if (current->token_type >= T_REDIR_IN
			&& current->token_type <= T_HEREDOC)
			if (check_redir(current) == 0)
				return (0);
		current = current->next;
	}
	return (1);
}
