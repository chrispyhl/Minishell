/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:17:16 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 21:52:23 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

char	*get_env_value(t_env_list *env, char *key)
{
	t_env_node	*current;
	size_t		key_len;

	if (!env || !key)
		return (NULL);
	current = env->head;
	key_len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->key, key, key_len + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	is_valid_env_key(char *key)
{
	int	i;
	
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
	return (0);
i++;
while (key[i])
{
	if (!ft_isalnum(key[i]) && key[i] != '_')
	return (0);
i++;
}	
return (1);
}

void	env_add_back(t_env_list *env, char *key, char *value)
{
	t_env_node *new_node;
	t_env_node *current;
	
	new_node = ft_malloc(sizeof(t_env_node), 1);
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!env->head)
	{
		env->head = new_node;
		env->tail = new_node;
	}
	else
	{
		if (env->tail)
		{
			env->tail->next = new_node;
			env->tail = new_node;
		}
		else
		{
			current = env->head;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
	}
	env->size++;
}

int	process_export_arg(t_env_list *env, char *arg)
{
	char		*key;
	char		*value;
	char		*equals_pos;
	size_t		key_len;
	t_env_node	*current;

	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
	{
		key_len = equals_pos - arg;
		key = ft_malloc(key_len + 1, 1);
		ft_strlcpy(key, arg, key_len + 1);
		value = gc_strdup(equals_pos + 1);
	}
	else
	{
		key = gc_strdup(arg);
		value = NULL;
	}
	if (!is_valid_env_key(key))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" - is not a valid identifier\n", 2);
		return (1);
	}
	current = env->head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (value != NULL)
				current->value = value;
			return (0);
		}
		current = current->next;
	}
	env_add_back(env, key, value);
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
