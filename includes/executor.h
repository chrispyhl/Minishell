/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:08:06 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/09 15:58:40 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./minishell.h"
# include "./garbage_collector.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

// EXECUTOR CORE

void		execute_command_list(t_cmd_list *list, t_env_list *env);
void		wait_for_all(t_env_list *env, pid_t last_pid);

int			handle_single_cmd(t_cmd_node *node, t_env_list *env);
int			execute_builtin(t_cmd_node *node, t_env_list *env);

// BUILTINS

int			handle_echo(t_cmd_node *node);
int			handle_pwd(void);
int			handle_env(t_env_list *env);
int			handle_cd(t_cmd_node *node, t_env_list *env);
int			handle_exit(t_cmd_node *node);
int			handle_export(t_cmd_node *node, t_env_list *env);
int			handle_unset(t_cmd_node *node, t_env_list *env);

// EXTERNALS

int			handle_external_cmd(t_cmd_node *node, t_env_list *env);

// EXTERNAL UTILITIES
char		*get_cmd_path(char *cmd, t_env_list *env);

// Piping

int			handle_piped_cmd(t_cmd_list *list, t_env_list *env);
int			handle_redirections(t_cmd_node *node, t_env_list *env);

// ENV UTILITIES

char		*get_env_value(t_env_list *env, char *key);
void		env_add_back(t_env_list *env, char *key, char *value);
void 		remove_env_node(t_env_list *env, char *key);
int			is_valid_env_key(char *key);
char		**env_list_to_array(t_env_list *env);
void		print_sorted_env(t_env_list *env);
void		set_env_value(t_env_list *env, char *key, char *value);

// OTHER UTILITIES

void		print_export_line(char *line);
int			process_export_arg(t_env_list *env, char *arg);
int			is_numeric(char *str);
int			err_msg(char *cmd, char *msg, int status);
int			get_exit_status(int status);
void		handle_wait_status(int status, t_env_list *env);

// Vorrübergehend

#endif