/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_expander_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:19:29 by craabe            #+#    #+#             */
/*   Updated: 2026/01/27 12:01:07 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*find_env_value(t_env_list *env_list, char *token, int len)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (ft_strncmp(current->key, token, len) == 0
			&& current->key[len] == '\0')
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	get_key_len(char *token)
{
	int	i;

	i = 1;
	if (token[i] == '?' || ft_isdigit(token[i]) == 1)
		return (1);
	while (ft_isalnum(token[i]) == 1 || token[i] == '_')
		i++;
	return (i - 1);
}

int	insert_value(t_token_node *current, char *key_pt, char *value, int key_len)
{
	char	*affix;
	char	*pre_val;
	char	*result;

	affix = gc_substr(current->token, 0, key_pt - current->token);
	if (!affix)
		return (-1);
	pre_val = gc_strjoin(affix, value);
	if (!pre_val)
		return (-1);
	affix = gc_substr(key_pt, key_len + 1, ft_strlen(key_pt));
	if (!affix)
		return (-1);
	result = gc_strjoin(pre_val, affix);
	if (!result)
		return (-1);
	current->token = result;
	return (0);
}

int	expand_token(t_token_node *current, t_env_list *env_list, int *i)
{
	char	*value;
	int		key_len;

	key_len = get_key_len(&current->token[*i]);
	if (current->token[(*i) + 1] == '?')
	{
		value = gc_itoa(env_list->exit_status);
		if (!value)
			return (-1);
		if (insert_value(current, &current->token[*i], value, key_len) == -1)
			return (-1);
		*i += ft_strlen(value);
	}
	else
	{
		value = find_env_value(env_list, &current->token[*i] + 1, key_len);
		if (!value)
			value = "";
		if (insert_value(current, &current->token[*i], value, key_len) == -1)
			return (-1);
		*i += ft_strlen(value);
	}
	return (0);
}

int	check_var_start(char c)
{
	if (ft_isalnum(c) == 1 || c == '_' || c == '?')
		return (1);
	return (0);
}
