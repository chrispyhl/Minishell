/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrispyshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:28 by craabe            #+#    #+#             */
/*   Updated: 2025/12/15 08:58:18 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: ctrl + C functionality via sigint handling
// partial input plus ctrl + C should keep input so far and open new prompt
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
			env_list = init_env_list(envp);
			cmd_list = parser(input, env_list);
			// exit condition for potential parser failure (?)
			// input of parsed data to executor here: executor(cmd_list)
			// exit condition for potential executor failure (?)
			// free cmd_list
			free(input);
		}
	}
	return (0);
}
