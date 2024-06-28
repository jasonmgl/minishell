/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:03:23 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 11:32:13 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(char *file, int flag)
{
	if (!file)
		return ;
	if (access(file, F_OK) == -1)
		print_file_error(file);
	else if (access(file, flag) == -1)
		print_permission_denied(file);
	else
		print_strerror();
}

int	open_in(char *file, int pipe_fd[2], int builtin)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		check_access(file, R_OK);
		dup2(pipe_fd[0], STDIN_FILENO);
		close_fds(pipe_fd);
		return (ERR);
	}
	if (builtin == false)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_out(char *file, int pipe_fd[2], int append, int do_dup)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (do_dup && fd != -1)
		dup2(fd, STDOUT_FILENO);
	else if (fd == -1)
	{
		check_access(file, W_OK);
		if (do_dup)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close_fds(pipe_fd);
		return (ERR);
	}
	close(fd);
	return (SUCCESS);
}

void	save_std_fd(t_data *data)
{
	data->fd_stdin = dup(STDIN_FILENO);
	data->fd_stdout = dup(STDOUT_FILENO);
}

void	restore_std_fd(t_data *data)
{
	dup2(data->fd_stdin, STDIN_FILENO);
	dup2(data->fd_stdout, STDOUT_FILENO);
	if (data->fd_stdin != -1)
		close(data->fd_stdin);
	if (data->fd_stdout != -1)
		close(data->fd_stdout);
}
