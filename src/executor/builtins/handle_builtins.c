/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:11:53 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/11 18:12:17 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include <limits.h>

// int	handle_cd(t_cmd_node *node)
// {
	
// }

// int	handle_echo(t_cmd_node *node)
// {
	
// }

int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, 1);
		free (cwd);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("getcwd failed to get working directory\n", 2);
	return (0);
}

// int	handle_export(t_cmd_node *node)
// {
	
// }

// int	handle_unset(t_cmd_node *node)
// {
	
// }
