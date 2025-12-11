/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:31:42 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/11 14:32:53 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

t_cmd_list	*setup_single_command_test(t_cmd_node *node)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)ft_malloc(sizeof(t_cmd_list), 1);
	if (!list)
		return (NULL);

	list->head = node;
	list->tail = node;
	list->size = 1;

	return (list);
}

char	**duplicate_cmd_args(const char **src)
{
	int		i;
	int		len;
	char	**dest;

	len = 0;
	while (src[len])
		len++;
	dest = (char **)ft_malloc(sizeof(char *) * (len + 1), 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = gc_strdup(src[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

t_cmd_node	*create_test_node(enum e_cmd_type type, const char **args)
{
	t_cmd_node	*node;
	char		**cmd_array;
	int			i;

	i = 0;
	while (args[i])
		i++;
	cmd_array = (char **)ft_malloc(sizeof(char *) * (i + 1), 1);
	if (!cmd_array)
		return (NULL);
	i = -1;
	while (args[++i])
		cmd_array[i] = gc_strdup(args[i]);
	cmd_array[i] = NULL;
	node->cmd_type = type;
	node->cmd = cmd_array;
	node->files = NULL;
	node->next = NULL;
	return (node);
}

void	test_case_1_external(void)
{
	const char	*ls_args[] = {"ls", "-l", NULL};
	t_cmd_node	*node = create_test_node(EXTERNAL, ls_args);
	t_cmd_list	*list = setup_single_command_test(node);

	if (list)
	{
		printf("\n[TEST 1] Aufruf: execute_command_list(ls -l, size=1, EXTERNAL_CMD)\n");
		// Der Aufruf, den Sie testen möchten
		execute_command_list(list);
	}
}

void	test_case_2_builtin(void)
{
	// Setup: echo hallo welt (Built-in Ausführung -> Direkter Funktionsaufruf im Parent)
	const char	*echo_args[] = {"echo", "hallo welt", NULL};
	t_cmd_node	*node = create_test_node(BUILDIN, echo_args);
	t_cmd_list	*list = setup_single_command_test(node);

	if (list)
	{
		printf("\n[TEST 2] Aufruf: execute_command_list(echo hallo welt, size=1, BUILTIN)\n");
		// Der Aufruf, den Sie testen möchten
		execute_command_list(list);
	}
}

int	main(void)
{
	gc_init();
	printf("--- Minishell Executor Tester Start ---\n");
	test_case_1_external();
	test_case_2_builtin();
	printf("--- Minishell Executor Test End ---\n");
	gc_free();
	return (0);
}
