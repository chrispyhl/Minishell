/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:17:22 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/10 13:56:27 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_cmd_list	*create_dummy_pipeline(void)
{
	t_cmd_list	*list;
	t_cmd_node	*cmd1;
	t_cmd_node	*cmd2;
	t_file_node	*file1;

	list = ft_malloc(1, sizeof(t_cmd_list));
	if (!list)
		return (NULL);

	// --- CMD 1: ls -l > out.txt ----------------------------------
	cmd1 = ft_malloc(1, sizeof(t_cmd_node));
	if (!cmd1)
		return (NULL);

	// 1a. cmd: ["ls", "-l", NULL]
	cmd1->cmd = ft_malloc(3, sizeof(char*));
	cmd1->cmd[0] = gc_strdup("ls");
	cmd1->cmd[1] = gc_strdup("-l");
	cmd1->cmd[2] = NULL;

	// 1b. files: > out.txt
	cmd1->files = ft_malloc(1, sizeof(t_file_list));
	file1 = ft_malloc(1, sizeof(t_file_node));
	file1->filename = gc_strdup("out.txt");
	file1->redir_type = 2; // > (Output)
	file1->next = NULL;

	cmd1->files->head = file1;
	cmd1->files->size = 1;
	cmd1->next = NULL; // Wird später auf cmd2 gesetzt

	// --- CMD 2: grep .c -----------------------------------------
	cmd2 = ft_malloc(1, sizeof(t_cmd_node));
	if (!cmd2)
		return (NULL);

	// 2a. cmd: ["grep", ".c", NULL]
	cmd2->cmd = ft_malloc(3, sizeof(char *));
	cmd2->cmd[0] = gc_strdup("grep");
	cmd2->cmd[1] = gc_strdup(".c");
	cmd2->cmd[2] = NULL;

	// 2b. files: (Keine Redirection, Input kommt von Pipe)
	cmd2->files = ft_malloc(1, sizeof(t_file_list));
	cmd2->files->size = 0;
	cmd2->next = NULL;

	// 3. Pipeline verknüpfen: cmd1 | cmd2
	cmd1->next = cmd2;
	list->head = cmd1;
	list->tail = cmd2;
	list->size = 2;

	return (list);
}
