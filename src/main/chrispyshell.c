/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrispyshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:28 by craabe            #+#    #+#             */
/*   Updated: 2026/01/06 13:20:33 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: ctrl + C functionality via sigint handling
// prior input is kept, but not executed, ^C is added
// new line gets opened
// void signal_handler(int code)
// {
// }

static t_env_list	*init_env_list(char **envp)
{
	t_env_list	*env_list;
	t_env_node	*env_node;
	int			i;

	env_list = malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->head = NULL;
	env_list->tail = NULL;
	env_list->size = 0;
	i = 0;
	while (envp[i])
	{
		env_node = create_env_node(envp[i]);
		if (!env_node)
		{
			free_env_list(env_list);
			return (NULL);
		}
		env_list_add_back(env_list, env_node);
		i++;
	}
	return (env_list);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_cmd_list	*cmd_list;
	t_env_list	*env_list;

	(void)argc;
	(void)argv;
	(void)cmd_list;
	cmd_list = NULL;
	env_list = init_env_list(envp);
	while (1)
	{
		// prompt string needs to be refined (include path? newline?)
		input = readline("chrispyshell: ");
		// handles ctrl + D
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			cmd_list = parser(input, env_list);
			// TODO: ERROR HANDLING HERE
			execute_command_list(cmd_list, env_list);
			// ERROR HANDLING HERE
			free_cmd_list(cmd_list); // if not used by executor
			free(input);
		}
	}
	return (0);
}
