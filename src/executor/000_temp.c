/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_temp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 11:07:32 by chris             #+#    #+#             */
/*   Updated: 2026/01/03 12:17:00 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

// In 9_0_utils.c (Beispielhaft, passt an eure Struktur an)
void	fix_broken_parser_node(t_cmd_node *node)
{
	int	i;

	i = 0;
	while (node->cmd && node->cmd[i])
	{
		if (ft_strcmp(node->cmd[i], ">") == 0 && node->cmd[i + 1])
		{
			// 1. Wir "klauen" den Dateinamen für die Redirection
			// Hier müsstet ihr eure Struktur füllen, z.B.:
			// node->redirection_file = gc_strdup(node->cmd[i + 1]);
			// node->redirection_type = NODE_OUTPUT;
			
			// 2. Wir simulieren touch direkt hier, um zu sehen ob es geht:
			int fd = open(node->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd != -1)
				close(fd);

			// 3. Wir löschen alles ab dem > aus dem Befehl
			node->cmd[i] = NULL;
			break ;
		}
		i++;
	}
}
