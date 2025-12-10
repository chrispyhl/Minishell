/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:38:26 by craabe            #+#    #+#             */
/*   Updated: 2025/12/10 17:19:55 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

typedef enum e_token_type
{
	WORD,      // general text (cmds, args, filenames)
	PIPE,      // |
	REDIR_IN,  // <
	REDIR_OUT, // >
	REDIT_APP, // >>
	HEREDOC    // <<
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

// token list helper ft
t_token_list			*create_token_node(char *content,
							enum e_token_type type);
void					token_list_add_back(t_token_list **head,
							t_token_list *new_node);

#endif
