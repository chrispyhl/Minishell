/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:26 by craabe            #+#    #+#             */
/*   Updated: 2026/01/07 14:34:59 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

typedef enum e_token_type
{
	T_WORD,      // general text (cmds, args, filenames)
	T_PIPE,      // |
	T_REDIR_IN,  // <
	T_REDIR_OUT, // >
	T_REDIR_APP, // >>
	T_HEREDOC    // <<
}						t_token_type;

typedef struct s_token_node
{
	char				*token;
	enum e_token_type	token_type;
	struct s_token_node	*next;
	struct s_token_node	*prev;
}						t_token_node;

typedef struct s_token_list
{
	t_token_node		*head;
	t_token_node		*tail;
	ssize_t				size;
}						t_token_list;

typedef enum e_expander_state
{
	STATE_DEFAULT,
	STATE_SINGLE,
	STATE_DOUBLE
}						t_expander_state;

// lexer
t_token_list			*lexer(char *input);

// expander
int						expander(t_token_list *token_list,
							t_env_list *env_list);

// lexer util
int						find_quote_end(char *seg, int *j);
int						create_redir_node_content(char *seg,
							char **node_content, t_token_type *redir_type);

// expander util
char					*find_env_value(t_env_list *env_list, char *token,
							int len);
int						get_key_len(char *token);
int						insert_value(t_token_node *current, char *key_pt,
							char *value, int key_len);
int						expand_token(t_token_node *current,
							t_env_list *env_list, int *i);
int						check_var_start(char c);

// token list util
t_token_list			*init_token_list(void);
t_token_node			*create_token_node(char *content, t_token_type type);
void					token_list_add_back(t_token_list *list,
							t_token_node *new_node);
void					free_token_node(t_token_node *token_node);
void	free_token_list(t_token_list *token_list);

// cmd list creation
t_cmd_list				*create_cmd_list(t_token_list *token_list);

// syntax validation
int						check_token_syntax(t_token_list *token_list);

// cmd_list_utils
t_redir_type			token_type_to_redir_type(t_token_type token_type);
int						extract_redirs(t_token_node *current,
							t_cmd_node *cmd_node);

// file list util
t_file_list				*init_file_list(void);
void					file_list_add_back(t_file_list *head,
							t_file_node *file_node);
t_file_node				*create_file_node(char *filename,
							t_redir_type redir_type);
void					free_file_list(t_file_list *file_list);

#endif
