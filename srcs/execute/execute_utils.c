/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:45:06 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 13:55:40 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_next_line(t_cmd **head, t_data *data)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
	{
		free_commands(data, head);
		free_data(data);
		exit(1);
	}
	if (expand(data, &line, true) == ERR)
	{
		free_commands(data, head);
		free_data(data);
		free(line);
		exit(1);
	}
	return (line);
}

static void	check_heredoc_files(t_cmd **head, t_cmd **cmd, t_data *data, int fd)
{
	if (fd == -1 || (*cmd)->infile == NULL)
	{
		free_commands(data, head);
		free_data(data);
		exit(1);
	}
}

void	do_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		print_strerror();
		exit(1);
	}
}

pid_t	do_fork(int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_strerror();
		close_fds(pipe_fd);
		exit(1);
	}
	return (pid);
}

int	read_lines(t_cmd **head, t_cmd **cmd, t_data *data, int j)
{
	char	*line;
	int		fd;
	size_t	length;
	t_sig	*sig;

	sig = get_sig();
	fd = open((*cmd)->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	sig->heredoc_fd = fd;
	check_heredoc_files(head, cmd, data, fd);
	line = read_next_line(head, data);
	length = max(ft_strlen(line) - 1, ft_strlen((*cmd)->delimiters[j]));
	while (line && ft_strncmp(line, (*cmd)->delimiters[j], length) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = read_next_line(head, data);
		length = max(ft_strlen(line) - 1, ft_strlen((*cmd)->delimiters[j]));
	}
	free(line);
	close(fd);
	close_fds((*cmd)->pfd);
	free_commands(data, head);
	free_data(data);
	exit(0);
}
