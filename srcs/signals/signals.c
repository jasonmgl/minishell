/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:03:46 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 16:07:43 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	*get_sig(void)
{
	static t_sig	sig;

	return (&sig);
}

void	signal_handler(int sign)
{
	t_sig	*sig;

	sig = get_sig();
	if (sign == SIGINT && sig->child)
	{
		write(STDERR_FILENO, "\n", 1);
		close_fds(sig->cmd[sig->i]->pfd);
		close(sig->heredoc_fd);
		unlink(sig->heredoc_infile);
		free_commands(sig->data, sig->cmd);
		free_data(sig->data);
		exit(128 + SIGINT);
	}
	if (sign == SIGQUIT && sig->child)
		write(STDERR_FILENO, "\b\b\033[K", 6);
	if (sign == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		sig->status = 130;
	}
}

void	signal_child_handler(int sign)
{
	(void) sign;
}

void	init_sig(void)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = 0;
	sig->child = 0;
	sig->sigint = 0;
	sig->i = 0;
	sig->heredoc_infile = NULL;
	sig->heredoc_fd = -1;
}

void	add_struct_to_sig(t_data *data, t_cmd **cmd)
{
	t_sig	*sig;

	sig = get_sig();
	sig->data = data;
	sig->cmd = cmd;
}
