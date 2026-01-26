/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:08:06 by cpohl             #+#    #+#             */
/*   Updated: 2026/01/26 20:00:34 by cpohl            ###   ########.fr       */
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

// Pipe info struct
typedef struct s_pipe_info
{
	int			*pipe_fds;
	int			prev_read;
	t_cmd_node	*node;
}				t_pipe_info;


// EXECUTOR CORE

void		execute_command_list(t_cmd_list *list, t_env_list *env);

int			handle_single_cmd(t_cmd_node *node, t_env_list *env);
int			execute_builtin(t_cmd_node *node, t_env_list *env, int saved_io[2]);

// BUILTINS

int			handle_echo(t_cmd_node *node);
int			handle_pwd(void);
int			handle_env(t_env_list *env);
int			handle_cd(t_cmd_node *node, t_env_list *env);
int			handle_exit(t_cmd_node *node, t_env_list *env, int saved_io[2]);
int			handle_export(t_cmd_node *node, t_env_list *env);
int			handle_unset(t_cmd_node *node, t_env_list *env);

void		print_export_line(char *line);
int			process_export_arg(t_env_list *env, char *arg);

// EXTERNALS

int			handle_external_cmd(t_cmd_node *node, t_env_list *env);
void		execute_binary(t_cmd_node *node, t_env_list *env);

char		*get_cmd_path(char *cmd, t_env_list *env);

// Piping

int			handle_piped_cmd(t_cmd_list *list, t_env_list *env);

// Redirecting

int			handle_redirections(t_cmd_node *node, t_env_list *env);

int			open_file(char *filename, int redir_type);
void		apply_fd_redir(int fd, int type);
int			check_is_directory(char *filename, int type);


// Heredoc

int			fork_heredoc(char *delimiter, t_env_list *env, int heredoc_quote);

char		*expand_heredoc_line(char *line, t_env_list *env, int heredoc_quote);
void		close_all_heredocs(t_cmd_list *list);
char		*append_char(char *line, int *i, char *new_line);
char		*append_var(char *line, int *i, t_env_list *env, char *new_line);
int			get_var_len(char *str);
void		close_inherited_fds(int keep_fd);
void		heredoc_sigint_handler(int sig);
void		handle_heredoc_eof(char *del, t_env_list *env, int pipe_fd);
void		process_heredoc_line(char *line, t_env_list *env, int pipe_fd, int hd_quote);
void		heredoc_cleanup_and_exit(t_env_list *env, int pipe_fd, int status);

// ENV UTILITIES

char		*get_env_value(t_env_list *env, char *key);
void		env_add_back(t_env_list *env, char *key, char *value);
void		remove_env_node(t_env_list *env, char *key);
int			is_valid_env_key(char *key);
char		**env_list_to_array(t_env_list *env);
void		print_sorted_env(t_env_list *env);
void		set_env_value(t_env_list *env, char *key, char *value);
int			append_env_value(t_env_list *env, char *key, char *value);
int			update_env_if_exists(t_env_list *env, char *key, char *value);

// OTHER UTILITIES

void		wait_for_all(t_env_list *env, pid_t last_pid);
int			is_numeric(char *str);
int			err_msg(char *msg, int status);
int			get_exit_status(int status);
void		full_cleanup(t_env_list *env);
void		update_underscore(t_env_list *env, char **cmd);

// Vorrübergehend

#endif