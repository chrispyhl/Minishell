/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_2_1more_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:43:08 by chris             #+#    #+#             */
/*   Updated: 2026/01/02 17:19:35 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	print_sorted_env(t_env_list *env)
{
	char	**env_arr;
	char	*temp;
	int		i;
	int		j;

	env_arr = env_list_to_array(env);
	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		j = i + 1;
		while (env_arr[j])
		{
			if (ft_strcmp(env_arr[i], env_arr[j]) > 0)
			{
				temp = env_arr[i];
				env_arr[i] = env_arr[j];
				env_arr[j] = temp;
			}
			j++;
		}	
		print_export_line(env_arr[i]);
		i++;
	}
}
