/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:47 by craabe            #+#    #+#             */
/*   Updated: 2026/01/07 16:46:57 by craabe           ###   ########.fr       */
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

// failsafe in case limits.h does not include PATH_MAX (depends on OS?)
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

// FILE STRUCTS
// -------------------
// this is not part of Daniel's guide but nice to have imo
typedef enum e_redir_type
{
	NODE_INPUT,  // <
	NODE_OUTPUT, // >
	NODE_APPEND, // >>
	NODE_HEREDOC // <<
}						t_redir_type;

typedef struct s_file_node
{
	char				*filename;
	enum e_redir_type	redir_type;
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
	EMPTY
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
	ssize_t				size;
	int					exit_status;
}						t_env_list;
// ~~~~~~~~~~~~~~~~~~~

// PARSER
// maybe the only parser function we need in this header
t_cmd_list				*parser(char *input, t_env_list *env_list);

// EXECUTOR
int						execute_command_list(t_cmd_list *list, t_env_list *env);

// ENVIRONMENTAL VARIABLES LIST
t_env_node				*create_env_node(char *info);
void					env_list_add_back(t_env_list *list,
							t_env_node *new_node);
int						set_filepath_envar(t_env_list *env_list,
							char *filepath);
void					free_env_list(t_env_list *env_list);

// cmd utility
void					free_cmd_list(t_cmd_list *cmd_list);
void					free_file_list(t_file_list *file_list);

// general utility
void					free_array(char **array);
long long				ft_atoll(const char *str, int *error);
int						ft_strcmp(const char *s1, const char *s2);

#endif
