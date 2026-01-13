
#include "../../includes/parser.h"

static t_env_node	*set_underscore_key(char *filepath)
{
	t_env_node	*new_node;
	char		*underscore_key;
	char		*filepath_copy;

	underscore_key = ft_strdup("_");
	if (!underscore_key)
		return (NULL);
	filepath_copy = ft_strdup(filepath);
	if (!filepath_copy)
	{
		free(underscore_key);
		return (NULL);
	}
	new_node = new_env_node(underscore_key, filepath_copy);
	if (!new_node)
		return (NULL);
	return (new_node);
}

// ft for changing the value of _ in env
int	set_filepath_envar(t_env_list *env_list, char *filepath)
{
	t_env_node	*current;
	t_env_node	*new_node;
	char		*filepath_copy;

	current = env_list->head;
	while (current)
	{
		// look for the key from parameter
		if (ft_strcmp(current->key, "_") == 0)
		{
			filepath_copy = ft_strdup(filepath);
			if (!filepath_copy)
				return (-1);
			// if key already has value, free it
			if (current->value)
				free(current->value);
			current->value = filepath_copy;
			return (0);
		}
		current = current->next;
	}
	new_node = set_underscore_key(filepath);
	if (!new_node)
		return (-1);
	env_list_add_back(env_list, new_node);
	return (0);
}
