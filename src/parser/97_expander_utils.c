

#include "../../includes/parser.h"

// helper is needed to find the value corresponding to the key in the token_node
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

// little helper is needed to get the right key string len
// starts with $, ends with space, equal sign or null term
int	get_key_len(char *token)
{
	int	i;

	i = 1; // start at 1 to skip $
	// edge cases $? and $1, $2, $3 ...
	if (token[i] == '?' || ft_isdigit(token[i]) == 1)
		return (1);
	// aside from ?, envars consist of num. and alph. chars
	while (ft_isalnum(token[i]) == 1 || token[i] == '_')
		i++;
	return (i - 1); // -1 since we do not want to include null term
}

int	insert_value(t_token_node *current, char *key_pt, char *value, int key_len)
{
	char	*affix;
	char	*pre_val;
	char	*result;

	affix = ft_substr(current->token, 0, key_pt - current->token);
	if (!affix)
		return (-1);
	pre_val = ft_strjoin(affix, value);
	free(affix);
	if (!pre_val)
		return (-1);
	affix = ft_substr(key_pt, key_len + 1, ft_strlen(key_pt));
	if (!affix)
	{
		free(pre_val);
		return (-1);
	}
	result = ft_strjoin(pre_val, affix);
	free(pre_val);
	free(affix);
	if (!result)
		return (-1);
	free(current->token);
	current->token = result;
	return (0);
}

int	expand_token(t_token_node *current, t_env_list *env_list, int *i)
{
	char	*value;
	int		key_len;

	key_len = get_key_len(&current->token[*i]);
	value = find_env_value(env_list, &current->token[*i] + 1, key_len);
	if (!value)
		value = "";
	if (insert_value(current, &current->token[*i], value, key_len) == -1)
		return (-1);
	*i += ft_strlen(value);
	return (0);
}

// small helper ft to avoid clutter in if statement in expander ft
int	check_var_start(char c)
{
	if (ft_isalnum(c) == 1 || c == '_' || c == '?')
		return (1);
	return (0);
}
