/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_chrispyshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:28 by craabe            #+#    #+#             */
/*   Updated: 2026/01/27 11:58:30 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	main_setup(char *argv[], char **envp, t_env_list **env_list)
{
	char	*filepath;

	gc_init();
	filepath = get_filepath(argv[0]);
	if (!filepath)
		return (-1);
	*env_list = init_env_list(envp);
	if (!*env_list)
	{
		free(filepath);
		return (-1);
	}
	update_shlvl(*env_list);
	if (set_filepath_envar(*env_list, filepath) == -1)
	{
		free(filepath);
		free_env_list(*env_list);
		return (-1);
	}
	free(filepath);
	setup_signals();
	return (0);
}

static int	chrispyshell_loop(t_env_list *env_list)
{
	char		*input;
	t_cmd_list	*cmd_list;

	input = readline(TEAL "chrispyshell$ " RESET);
	sync_exit_status(env_list);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	else if (input[0] != '\0')
	{
		add_history(input);
		cmd_list = parser(input, env_list);
		if (cmd_list)
			execute_command_list(cmd_list, env_list);
		free(input);
	}
	else
		free(input);
	gc_free();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env_list;
	int			ret;

	ret = 0;
	(void)argc;
	env_list = NULL;
	if (main_setup(argv, envp, &env_list) == -1)
	{
		ft_putstr_fd("chrispyshell: malloc error\n", 2);
		return (1);
	}
	while (ret != -1)
		ret = chrispyshell_loop(env_list);
	if (env_list)
		free_env_list(env_list);
	clean_up();
	exit (0);
}
