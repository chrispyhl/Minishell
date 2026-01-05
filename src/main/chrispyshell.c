/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrispyshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:28 by craabe            #+#    #+#             */
/*   Updated: 2026/01/05 16:29:23 by gries            ###   ########.fr       */
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

// the contents of argv[0] depend on how the program was called
// ./chrispyshell --> relative path in argv
// /home/example/chrispyshell --> absolute path
// to unify, this ft will return the full path in any case
static char	*get_filepath(char *path)
{
	char	cwd[PATH_MAX];
	char	*result;
	char	*temp;

	// if it starts with a slash, it is abolute already
	if (path[0] == '/')
		// returning ft_strdup so this also returns malloced string
		return (ft_strdup(path));
	// if it starts with ., the path is relative
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (NULL);
	temp = ft_strjoin(cwd, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, path);
	free(temp);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_cmd_list	*cmd_list;
	t_env_list	*env_list;
	char		*filepath;

	(void)argc;
	cmd_list = NULL;
	// get absolute filepath of our executable
	filepath = get_filepath(argv[0]);
	if (!filepath)
		return (1);
	// put that filepath
	env_list = init_env_list(envp);
	if (!env_list)
	{
		free(filepath);
		free_env_list(env_list);
		return (1);
	}
	// put the absolute filepath into our env_list
	set_filepath_evnar(env_list, filepath);
	while (1)
	{
		// prompt string needs to be refined (include path? newline?)
		input = readline("chrispyshell$ ");
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
			if (cmd_list)
				execute_command_list(cmd_list, env_list);
			// TODO: MASSIVE ERROR HANDLING HERE
			free_cmd_list(cmd_list); // if not used by executor?
			free(input);
		}
	}
	// TODO: free env_list! this also frees filepath!
	return (0);
}
