/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:45:06 by rsequeir          #+#    #+#             */
/*   Updated: 2024/04/25 12:03:57 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		print_strerror();
		exit(ERR);
	}
}

void	close_fds(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

pid_t	do_fork(int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_strerror();
		close_fds(pipe_fd);
		exit(ERR);
	}
	return (pid);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	get_alnum(int fd)
{
	char c;

	c = 0;
	while (!ft_isalnum(c))
	{
		if (!read(fd, &c, 1))
			return (0);
		c = (char) (((unsigned char) c) % 126);
	}
	return (c);
}

char	*create_tmp_file(void)
{
	int		fd;
	int		i;
	char	*file;

	file = ft_calloc(21, sizeof(char));
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	file = ft_strdup("/goinfre/");
	i = 9;
	while (i < 20)
		file[i++] = get_alnum(fd);
	close(fd);
	return (file);
}

int	read_lines(t_cmd **cmd)
{
	char	*line;
	int		length;
	int		fd;
	t_sig	*sig;

	sig = get_sig();
	sig->child = 1;
	fd = open((*cmd)->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(ERR);
	line = get_next_line(STDIN_FILENO);
	length = max(ft_strlen(line) - 1, ft_strlen((*cmd)->delimiter));
	if (!(*cmd)->infile)
		exit(ERR);
	while (line && ft_strncmp(line, (*cmd)->delimiter, length) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
		length = max(ft_strlen(line) - 1, ft_strlen((*cmd)->delimiter));
	}
	free(line);
	close(fd);
	close_fds((*cmd)->pipe_fd);
	exit(SUCCESS);
}
