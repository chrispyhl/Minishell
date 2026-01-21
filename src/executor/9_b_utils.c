/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_b_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:30:53 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 16:48:53 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	parse_export_key_value(char *arg, char **key, char **value, int *append)
{
	char	*equals;

	*append = 0;
	*value = NULL;
	equals = ft_strchr(arg, '=');
	if (equals && equals > arg && *(equals - 1) == '+') // Wenn '+=' gefunden wird
	{
		*append = 1;
		*key = ft_substr(arg, 0, equals - arg - 1);
		*value = ft_strdup(equals + 1);
	}
	else if (equals) // Wenn '=' gefunden wird
	{
		*key = ft_substr(arg, 0, equals - arg);
		*value = ft_strdup(equals + 1);
	}
	else
		*key = ft_strdup(arg);
}

static int	set_export_value(t_env_list *env, char *key, char *value, int append)
{
	if (append) // wenn Anhängeflag gesetzt ist
	{
		if (append_env_value(env, key, value) == 0) // versuche anzuhängen
			set_env_value(env, key, value); // wenn nicht existent, setze neuen Wert
	}
	else
	{
		if (update_env_if_exists(env, key, value) == 0) // versuche zu aktualisieren
			env_add_back(env, key, value); // wenn nicht existent, füge neuen Eintrag hinzu
	}
	return (0);
}

int	process_export_arg(t_env_list *env, char *arg)
{
	char	*key;
	char	*value;
	int		append;

	parse_export_key_value(arg, &key, &value, &append); // Schlüssel, Wert und Anhängeflag parsen
	if (!is_valid_env_key(key)) // Überprüfe, ob der Schlüssel gültig ist
	{
		free(key); // Wenn nicht gültig, Speicher freigeben
		free(value);
		return (err_msg("not a valid identifier", 1));
	}
	set_export_value(env, key, value, append); // Setze oder hänge den Wert an die Umgebungsvariable an
	free(key);
	free(value);
	return (0);
}

void	print_export_line(char *line)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (line[i] && line[i] != '=')
		ft_putchar_fd(line[i++], 1);
	if (line[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(&line[i + 1], 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
}
