/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_0_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:10 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/21 16:48:32 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	err_msg(char *msg, int status)
{
	ft_putstr_fd("chrispyshell: ", 2);
	ft_putendl_fd(msg, 2);
	return (status);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
