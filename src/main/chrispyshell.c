/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrispyshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:28 by craabe            #+#    #+#             */
/*   Updated: 2026/01/07 22:04:55 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define TEAL "\001\033[1;36m\002"
#define RESET "\001\033[0m\002"

volatile sig_atomic_t	g_signal = 0;
// volatile: tells compiler optimization:
// "don't skip scanning this value again for better effiency! might change anytime!"
// sig_atomic_t: integer type that guarantees uninterrupted reading regardless of hardware

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
	env_list->exit_status = 0;
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
	{
		ft_putstr_fd("chrispyshell: malloc error\n", 2);
		return (1);
	}
	env_list = init_env_list(envp);
	if (!env_list)
	{
		free(filepath);
		ft_putstr_fd("chrispyshell: malloc error\n", 2);
		return (1);
	}
	// put the absolute filepath into our env_list
	if (set_filepath_envar(env_list, filepath) == -1)
	{
		free(filepath);
		free_env_list(env_list);
		ft_putstr_fd("chrispyshell: malloc error\n", 2);
		return (1);
	}
	free(filepath);
	// setup for handling
	// SIGINT (signal interrupt, ctrl + c)
	// and SIGQUIT (ctrl + \)
	setup_signals();
	while (1)
	{
		// this means that SIGINT (ctrl + C) was entered!
		if (g_signal == 2)
		{
			env_list->exit_status = 130;
			g_signal = 0;
		}
		// prompt string needs to be refined (include path? newline?)
		input = readline(TEAL"chrispyshell$ "RESET);
		// handles ctrl + D
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			free_env_list(env_list);
			exit(0);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			cmd_list = parser(input, env_list);
			if (cmd_list)
			{
				execute_command_list(cmd_list, env_list);
				free_cmd_list(cmd_list);
			}
			// TODO: MASSIVE ERROR HANDLING HERE
			free(input);
		}
		else
			free(input); // free input upon after blank line ENTER
	}
	// TODO: free env_list! this also frees filepath!
	return (0);
}
