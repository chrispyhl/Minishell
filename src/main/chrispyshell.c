/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrispyshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:28 by craabe            #+#    #+#             */
/*   Updated: 2025/12/09 16:28:47 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// handles sigint = ctrl + C signal
// void signal_handler(int code)
// {

// }

int	main(void)
{
	char	*input;

	while (1)
	{
		// prompt string needs to be refined (include path? newline?)
		input = readline("chrispyshell: ");
		// handles ctrl + D
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			// input to parser here
			// exit condition for potential parser failure (?)
			// input of parsed data to executor here
			// exit condition for potential executor failure (?)}
			free(input);
		}
	}
	return (0);
}
