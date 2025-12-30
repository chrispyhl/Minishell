/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:05:11 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/30 15:34:18 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "../libft/src/libft.h"

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc_list
{
	t_gc_node	*head;
	t_gc_node	*tail;
	size_t		size;	
}				t_gc_list;

// ft_malloc.c
void	*ft_malloc(size_t count, size_t size);

//	gc_utils.c
void		clean_up(void);
void		gc_init(void);
void		gc_add(void *ptr);
void		gc_free(void);
t_gc_list	*get_gc(void);

//	gc_libft.c
char	*gc_itoa(int n);
char	**gc_split(char const *s, char c);
char	*gc_substr(char const *s, unsigned int start, size_t len);
char	*gc_strdup(const char *s1);
char	*gc_strjoin(char const *s1, char const *s2);


#endif