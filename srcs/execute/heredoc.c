/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:19:59 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 16:32:36 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_heredoc(t_sig *sig)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	while (pid != -1)
	{
		if (WIFEXITED(status))
		{
			sig->status = WEXITSTATUS(status);
			if (sig->status == (128 + SIGINT))
				sig->sigint = 1;
		}
		pid = wait(&status);
	}
}

static void	do_heredoc(t_cmd **head, t_cmd **cmd, t_data *data, int j)
{
	pid_t	pid;
	t_sig	*sig;

	sig = get_sig();
	do_pipe((*cmd)->pfd);
	signal(SIGINT, signal_child_handler);
	pid = do_fork((*cmd)->pfd);
	if (pid == 0)
	{
		sig->child = 1;
		sig->heredoc_infile = (*cmd)->infile;
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		read_lines(head, cmd, data, j);
	}
	if (j == ((*cmd)->here_doc - 1))
		dup2((*cmd)->pfd[0], STDIN_FILENO);
	close_fds((*cmd)->pfd);
	wait_heredoc(sig);
}

int	has_heredoc(t_data *data, t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while (i < data->nbr_cmd)
	{
		if (cmd[i++]->here_doc)
			return (1);
	}
	return (0);
}

void	try_do_heredoc(t_data *data, t_cmd **head, t_cmd **cmd, size_t j)
{
	t_sig	*sig;

	sig = get_sig();
	if (sig->sigint == 0)
	{
		if ((*cmd)->i != 0)
			dup2(data->fd_stdin, STDIN_FILENO);
		do_heredoc(head, cmd, data, j);
	}
}

void	exec_heredoc(t_data *data, t_cmd **cmd)
{
	size_t	i;
	size_t	j;
	t_sig	*sig;
	char	*tmp_file;

	sig = get_sig();
	i = 0;
	tmp_file = NULL;
	while (i < data->nbr_cmd)
	{
		if (cmd[i]->here_doc)
		{
			j = 0;
			while (j < (size_t) cmd[i]->here_doc)
			{
				if (tmp_file)
					free(tmp_file);
				tmp_file = create_tmp_file();
				cmd[i]->infile = tmp_file;
				try_do_heredoc(data, cmd, &cmd[i], j);
				j++;
			}
		}
		i++;
	}
}
