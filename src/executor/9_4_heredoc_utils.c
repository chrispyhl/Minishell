/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_4_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:38:02 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 15:38:23 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

char	*append_var(char *line, int *i, t_env_list *env, char *new_line)
{
	char	*var_name;
	char	*var_value;
	char	*old;
	int		var_len;

	var_len = get_var_len(&line[*i + 1]);
	var_name = ft_substr(line, *i + 1, var_len);
	var_value = get_env_value(env, var_name);
	if (var_value)
	{
		old = new_line;	
		new_line = ft_strjoin(new_line, var_value);
		free(old);
	}
	free(var_name);
	*i += var_len + 1;
	return (new_line);
}

int	get_var_len(char *str)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[len]))
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
