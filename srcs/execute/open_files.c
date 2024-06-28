/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:05:04 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/13 17:38:11 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_open_infile(t_data *data, t_cmd **head, t_cmd **cmd, pid_t pid)
{
	t_sig	*sig;

	sig = get_sig();
	if ((*cmd)->fd_in)
	{
		(*cmd)->fd_in = open_in((*cmd)->infile, (*cmd)->pfd, (*cmd)->builtin);
		if ((*cmd)->fd_in)
		{
			close_fds((*cmd)->pfd);
			if (pid == 0)
			{
				free_commands(data, head);
				free_data(data);
				exit(1);
			}
			sig->status = 1;
			return (ERR);
		}
	}
	return (SUCCESS);
}

static int	open_out_error(t_data *data, t_cmd **head, t_cmd **cmd, pid_t pid)
{
	t_sig	*sig;

	sig = get_sig();
	close_fds((*cmd)->pfd);
	if (pid == 0)
	{
		free_commands(data, head);
		free_data(data);
		exit(1);
	}
	sig->status = 1;
	return (ERR);
}

static int	do_open_outfiles(t_data *data, t_cmd **head, t_cmd **cmd, pid_t pid)
{
	size_t	n;
	size_t	i;
	int		do_dup;

	n = get_array_length((*cmd)->outs);
	i = 0;
	if ((*cmd)->outs[0])
	{
		while ((*cmd)->outs[i])
		{
			do_dup = i == (n - 1);
			if (open_out((*cmd)->outs[i], (*cmd)->pfd, (*cmd)->append, do_dup))
				return (open_out_error(data, head, cmd, pid));
			i++;
		}
	}
	else if ((*cmd)->last == false)
		dup2((*cmd)->pfd[1], STDOUT_FILENO);
	return (SUCCESS);
}

int	open_files(t_data *data, t_cmd **head, t_cmd **cmd, pid_t pid)
{
	if (do_open_infile(data, head, cmd, pid)
		|| do_open_outfiles(data, head, cmd, pid))
		return (ERR);
	return (SUCCESS);
}

void	close_fds(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
