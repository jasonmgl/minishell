/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:03:23 by rsequeir          #+#    #+#             */
/*   Updated: 2024/04/23 14:33:12 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(char *file)
{
	// A MODIFIER
	if (!file)
		return ;
	if (access(file, F_OK) == -1)
		print_file_error(file);
	else if (access(file, R_OK) == -1)
		print_permission_denied(file);
	else
		print_strerror();
}

int	open_infile(char *file, int pipe_fd[2])
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		check_access(file);
		dup2(pipe_fd[0], STDIN_FILENO);
		close_fds(pipe_fd);
		return (ERR);
	}
	dup2(fd, STDIN_FILENO);
	if (close(fd) == -1)
		print_strerror();
	return (SUCCESS);
}

int	open_outfile(char *file, int pipe_fd[2], int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		check_access(file);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_fds(pipe_fd);
		return (ERR);
	}
	dup2(fd, STDOUT_FILENO);
	if (close(fd) == -1)
		print_strerror();
	return (SUCCESS);
}
