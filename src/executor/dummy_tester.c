/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:15:13 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/10 15:18:06 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_list	*init_file_list(void)
{
	t_file_list	*list;
	list = (t_file_list *)ft_malloc(sizeof(t_file_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_cmd_list	*init_cmd_list(void)
{
	t_cmd_list	*list;
	list = (t_cmd_list *)ft_malloc(sizeof(t_cmd_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

// --- NUR DIE HARDCODED BEISPIELFUNKTION ---

/**
 * @brief Hardcoded Beispiel für: "cat file.c | grep include > header_use.txt"
 * * @return t_cmd_list* Die fertig aufgebaute Struktur.
 */
t_cmd_list	*get_hardcoded_pipeline_dummy(void)
{
	t_cmd_list	*list;
	t_cmd_node	*cmd1;
	t_cmd_node	*cmd2;
	t_file_list	*files2;

	// Init der Hauptliste
	list = init_cmd_list();
	if (!list)
		return (NULL);

	// --- 1. Befehl: cat file.c ---
	// Achtung: Wir verwenden Stack-Literale für char**. Diese NICHT free'n!
	cmd1 = (t_cmd_node *)ft_malloc(sizeof(t_cmd_node));
	if (!cmd1)
		return (NULL);
	cmd1->cmd_type = EXTERNAL;
	cmd1->cmd = (char *[]){"cat", "file.c", NULL};
	cmd1->files = NULL;
	cmd1->next = NULL;
	list->head = cmd1; // Kopf setzen
	list->size = 1;

	// --- 2. Befehl: grep include > header_use.txt ---
	// a) Redirection Liste erstellen
	files2 = init_file_list();
	if (!files2)
		return (NULL);
	t_file_node *redir_node = (t_file_node *)ft_malloc(sizeof(t_file_node));
	if (!redir_node)
		return (NULL);
	redir_node->filename = "header_use.txt";
	redir_node->redir_type = NODE_OUTPUT;
	redir_node->next = NULL;
	files2->head = redir_node;
	files2->tail = redir_node;
	files2->size = 1;

	// b) Befehlsknoten erstellen
	cmd2 = (t_cmd_node *)ft_malloc(sizeof(t_cmd_node));
	if (!cmd2)
		return (NULL);
	cmd2->cmd_type = EXTERNAL;
	cmd2->cmd = (char *[]){"grep", "include", NULL};
	cmd2->files = files2; // Redirection anhängen
	cmd2->next = NULL;
	
	// c) Verknüpfung (Pipe)
	cmd1->next = cmd2;
	list->tail = cmd2; // Ende setzen
	list->size = 2;

	return (list);
}

// --------------------------------------------------------------------------

int	main(void)
{
	t_cmd_list	*pipeline;

	printf("Starte Executor-Test mit Dummy-Pipeline: \"cat file.c | grep include > header_use.txt\"\n\n");

	// Hole die hartecodierte Struktur
	pipeline = get_hardcoded_pipeline_dummy();
	if (!pipeline)
		return (1);

	// HIER BEGINNT DEIN EXECUTOR CODE (z.B. executor_start(pipeline); )
	t_cmd_node *current_cmd = pipeline->head;
	printf("Executor startet mit %zd Befehlen:\n", pipeline->size);

	while (current_cmd)
	{
		printf("-------------------------------------------\n");
		printf("Befehl: %s\n", current_cmd->cmd[0]);

		// 1. Argumente verarbeiten:
		// Beispiel: Den kompletten Pfad zu 'cat' oder 'grep' finden und execve vorbereiten
		printf("  -> Auszuführendes Programm und Argumente: ");
		int i = 0;
		while (current_cmd->cmd[i])
			printf("%s ", current_cmd->cmd[i++]);
		printf("\n");

		// 2. Redirections verarbeiten:
		// Beispiel: Fd's setzen (open, dup2)
		if (current_cmd->files)
		{
			t_file_node *file = current_cmd->files->head;
			printf("  -> Redirection gefunden: %s (%s)\n", 
				file->filename, file->redir_type == NODE_OUTPUT ? "OUTPUT >" : "UNKNOWN");
		}

		// 3. Pipe-Logik verarbeiten:
		// Beispiel: Wenn current_cmd->next nicht NULL ist, muss ein Pipe erstellt werden.
		if (current_cmd->next)
			printf("  -> PIPE zur nächsten t_cmd_node erforderlich.\n");
		else
			printf("  -> Letzter Befehl in der Pipeline.\n");

		current_cmd = current_cmd->next;
	}
	printf("-------------------------------------------\n");
	
	// HIER WÜRDEST DU DEINEN FREE CALLEN
	// free_cmd_list(pipeline); 

	return (0);
}
