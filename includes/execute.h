/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:32:37 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 16:17:58 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "struct.h"

int		append(char ***array, char *str);
void	check_access(char *file, int flag);
void	close_fds(int pipe_fd[2]);
char	*create_tmp_file(void);
void	delete_tmp_files(t_data *data, t_cmd **cmd);
pid_t	do_fork(int pipe_fd[2]);
void	do_pipe(int pipe_fd[2]);
void	exec_builtin_func(t_cmd **head, t_cmd **cmd, t_data *data, pid_t pid);
void	exec_builtin(t_cmd **head, t_cmd **cmd, t_data *data, pid_t *last_pid);
void	exec_heredoc(t_data *data, t_cmd **cmd);
int		execute_all(t_data *data);
void	free_commands(t_data *data, t_cmd **cmd);
void	free_split(char **split);
size_t	get_array_length(char **array);
char	*get_command_path(char *command, char **envp, int *status);
char	**get_env_path(char **envp);
int		has_heredoc(t_data *data, t_cmd **cmd);
int		initialize_commands(t_cmd ***cmd, t_data *data);
int		open_files(t_data *data, t_cmd **head, t_cmd **cmd, pid_t pid);
int		open_in(char *file, int pipe_fd[2], int builtin);
int		open_out(char *file, int pipe_fd[2], int append, int do_dup);
int		parse_token(t_token *token, t_cmd **cmd);
void	print_command_not_found(char *command);
void	print_file_error(char *file);
void	print_permission_denied(char *arg);
void	print_strerror(void);
int		read_lines(t_cmd **head, t_cmd **cmd, t_data *data, int j);
void	restore_std_fd(t_data *data);
void	save_std_fd(t_data *data);
char	*search_in_path(char *command, char **path);
int		single_builtin(t_data *data, t_cmd *cmd);
char	**t_envp_to_array(t_envp *env);

#endif