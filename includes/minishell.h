/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:47 by craabe            #+#    #+#             */
/*   Updated: 2025/12/11 16:33:58 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include "garbage_collector.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>  // readline, perror
# include <stdlib.h> // malloc, free, exit

// FILE STRUCTS
// -------------------
// this is not part of Daniel's guide but nice to have imo
typedef enum e_redir_mode
{
	NODE_INPUT,  // <
	NODE_OUTPUT, // >
	NODE_APPEND, // >>
	NODE_HEREDOC // <<
}						t_redir_mode;

typedef struct s_file_node
{
	char				*filename;
	enum e_redir_mode	redir_type;
	struct s_file_node	*next;
}						t_file_node;
/*
filename = string with filename
redir_type = shows what kind of operator
next = pointer to next node
*/
typedef struct s_file_list
{
	t_file_node			*head;
	t_file_node			*tail;
	ssize_t				size;
}						t_file_list;
// -------------------

// COMMAND STRUCTS
// -------------------
// this is not part of Daniel's guide but nice to have imo
typedef enum e_cmd_type
{
	BUILTIN,
	EXTERNAL,
	PIPE,    // perhaps not necessary since handled by next pointers
	REDIRECT // perhaps not necessary since handled by t_file_list/t_file_node
}						t_cmd_type;

typedef struct s_cmd_node
{
	enum e_cmd_type		cmd_type;
	char				**cmd;
	t_file_list			*files;
	struct s_cmd_node	*next;
}						t_cmd_node;
/*
cmd_type = specifies type of command
cmd = array of strings for command arguments
files = pointer to meta struct
next = pointer to next node in list
*/
typedef struct s_cmd_list
{
	t_cmd_node			*head;
	t_cmd_node			*tail;
	ssize_t				size;
}						t_cmd_list;
// -------------------

// OUR OWN STRUCTS
// ~~~~~~~~~~~~~~~~~~~
typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_env_list
{
	t_env_node			*head;
	t_env_node			*tail;
	int					size;

}						t_env_list;
// ~~~~~~~~~~~~~~~~~~~
// maybe the only parser function we need in this header
t_cmd_list				*parser(char *input);

#endif
