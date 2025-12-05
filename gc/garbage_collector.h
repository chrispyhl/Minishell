/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:05:11 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/05 18:11:10 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "../libft/src/libft.h"

typedef struct s_gc_node
{
	void				*data;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc_list
{
	t_gc_node	*head;
	t_gc_node	*tail;
	size_t		size;	
}				t_gc_list;

#endif