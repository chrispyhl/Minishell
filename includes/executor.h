/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:08:06 by cpohl             #+#    #+#             */
/*   Updated: 2025/12/12 21:00:42 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./minishell.h"
# include "./garbage_collector.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>

t_cmd_node	*create_test_node(enum e_cmd_type type, const char **args);
t_env_node	*create_test_env_node(char *key, char *value);
t_env_list  *create_dummy_env_list(void);
t_cmd_list	*setup_single_command_test(t_cmd_node *node);
void		test_case_1_external(void);
void		test_case_2_builtin(void);
void		test_case_3_builtin(void);
void		test_case_4_env(void);

int			execute_command_list(t_cmd_list *list, t_env_list *env);

int			handle_single_cmd(t_cmd_node *node, t_env_list *env);
int			execute_builtin(t_cmd_node *node, t_env_list *env);


int			handle_echo(t_cmd_node *node);
int			handle_pwd(void);
int			handle_env(t_env_list *env);
int			handle_cd(t_cmd_node *node, t_env_list *env);

char		*get_env_value(t_env_list *env, char *key);


#endif