/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_handle_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:11:53 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 17:49:49 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	update_env_pwd(t_env_list *env, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0); // Hole das aktuelle Arbeitsverzeichnis
	if (!new_pwd)
		return ;
	set_env_value(env, "OLDPWD", old_pwd); // Aktualisiere OLDPWD
	set_env_value(env, "PWD", new_pwd); // Aktualisiere PWD
	free(new_pwd);
}

static int	is_valid_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	handle_cd(t_cmd_node *node, t_env_list *env)
{
	char	*path;
	char	old_pwd[1024];

	if (node->cmd[1] && node->cmd[2]) // Zu viele Argumente
		return (err_msg("too many arguments", 1));
	if (!getcwd(old_pwd, sizeof(old_pwd))) // speichere das aktuelle Verzeichnis
		return (1);
	path = node->cmd[1];
	if (!path || !*path) // kein Argument gegeben oder leeres Argument
		return (err_msg("HOME not set", 1));
	if (chdir(path) != 0) // wechsle das Verzeichnis
		return (perror("chrispyshell: cd"), 1);
	update_env_pwd(env, old_pwd); // aktualisiere PWD und OLDPWD in der Umgebung
	return (0);
}

int	handle_echo(t_cmd_node *node)
{
	int		i;
	int		n;

	n = 1; // standardmäßig new line ausgeben
	i = 1; // starte bei erstem Argument
	while (node->cmd[i] && is_valid_n(node->cmd[i])) // schleife durch alle -n Argumente
	{
		n = 0; // kein new line ausgeben
		i++;
	}
	while (node->cmd[i]) // gebe alle restlichen Argumente aus
	{
		ft_putstr_fd(node->cmd[i], 1);
		if (node->cmd[i + 1])
			ft_putstr_fd(" ", 1); // leerzeichen zwischen Argumenten
		i++;
	}
	if (n == 1)
		ft_putstr_fd("\n", 1); // new line am Ende, falls -n nicht gesetzt ist
	return (0);
}

int	handle_export(t_cmd_node *node, t_env_list *env)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!node->cmd[1]) // kein Argument
	{
		print_sorted_env(env); // gebe alle Umgebungsvariablen sortiert aus
		return (0);
	}
	i = 1;
	while (node->cmd[i])
	{
		if (process_export_arg(env, node->cmd[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
