/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:03:46 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 18:23:06 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	*get_sig(void)
{
	static t_sig	sig;

	return (&sig);
}

void	handle_sigint(t_sig *sig)
{
	if (sig->heredoc && sig->child)
		exit(sig->status);
	if (sig->work)
		write(STDERR_FILENO, "\n", 1);
	if (!sig->work)
	{
		write(STDERR_FILENO, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(t_sig *sig)
{
	if (sig->heredoc && sig->child)
		exit(sig->status);
	if (sig->work && !sig->heredoc)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		rl_replace_line("", 0);
	}
	else if (sig->work && sig->heredoc)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
	}
}

void	signal_handler(int sign)
{
	t_sig	*sig;

	sig = get_sig();
	sig->sig = sign;
	if (sign == SIGINT)
		handle_sigint(sig);
	else if (sign == SIGQUIT)
		handle_sigquit(sig);
}

void	init_sig(void)
{
	t_sig	*sig;
	size_t	i;
	
	sig = get_sig();
	sig->sig = 0;
	sig->work = 0;
	sig->status = 0;
	sig->heredoc = 0;
	i = 0;
	while (i < _NSIG)
	{
		if (i != SIGCHLD)
			signal(i, SIG_IGN);
		i++;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	rl_catch_signals = 0;
}
