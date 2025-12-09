/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:47 by craabe            #+#    #+#             */
/*   Updated: 2025/12/09 15:15:55 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include "./executor.h"
# include "./parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>  // readline, perror
# include <stdlib.h> // malloc, free, exit

typedef enum e_redir_mode
{
	NODE_INPUT,  // <
	NODE_OUTPUT, // >
	NODE_APPEND, // >>
	NODE_HEREDOC // <<
}					t_redir_mode;

typedef struct s_redir
{
	t_redir_mode	mode;
	char			*file;
	struct s_redir	*next;
}					t_redir;
// file = file name or heredoc delimiter

typedef struct s_cmd
{
	t_list			*args;
	int arg_c;		// perhaps not necessary, might want to remove later
	int	*redirs;
	struct s_cmd	*next;
}					t_cmd;
// t_list *args needs to be converted to a string array
// before it can be passed to executor

#endif
