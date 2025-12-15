/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:26 by craabe            #+#    #+#             */
/*   Updated: 2025/12/15 10:53:21 by gries            ###   ########.fr       */
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

typedef struct s_token_list
{
	char				*token;
	enum e_token_type	token_type;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}						t_token_list;

// lexer
t_token_list			*lexer(char *input);

// expander
int						expander(t_token_list *token_list,
							t_env_list *env_list);

// lexer util
int						find_quote_end(char *seg, int *j);
int						create_redir_node_content(char *seg,
							char **node_content, t_token_type *redir_type);

// token list util
t_token_list			*create_token_node(char *content,
							enum e_token_type type);
void					token_list_add_back(t_token_list **head,
							t_token_list *new_node);
void					free_token_list(t_token_list *token_list);

#endif
