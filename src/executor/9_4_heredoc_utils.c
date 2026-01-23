/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_4_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:38:02 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/23 15:54:32 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	close_heredocs_in_cmd(t_cmd_node *cmd)
{
	t_file_node	*file;

	if (!cmd || !cmd->files)
		return ;
	file = cmd->files->head;
	while (file)
	{
		if (file->redir_type == NODE_HEREDOC && file->heredoc_fd != -1)
		{
			close(file->heredoc_fd);
			file->heredoc_fd = -1;
		}
		file = file->next;
	}
}

void	close_all_hd_in_parent(t_cmd_list *list)
{
	t_cmd_node	*cmd;

	cmd = list->head;
	while (cmd)
	{
		close_heredocs_in_cmd(cmd);
		cmd = cmd->next;
	}
}

char	*append_char(char *line, int *i, char *new_line)
{
	char	*temp;
	char	*old;

	temp = ft_substr(line, (*i)++, 1);
	old = new_line;
	new_line = ft_strjoin(new_line, temp);
	free(old);
	free(temp);
	return (new_line);
}

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
