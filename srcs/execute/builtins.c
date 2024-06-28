/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:16:05 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/13 15:07:43 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_builtin(t_data *data, t_cmd *cmd)
{
	return (data->nbr_cmd == 1 && cmd->builtin);
}

void	exec_builtin_func(t_cmd **head, t_cmd **cmd, t_data *data, pid_t pid)
{
	if (open_files(data, head, cmd, pid) == ERR)
		return ;
	if (str_is_equal((*cmd)->command[0], "echo"))
	{
		if ((*cmd)->command[1])
			echo(&(*cmd)->command[1]);
		else
			echo(NULL);
	}
	else if (str_is_equal((*cmd)->command[0], "cd"))
		cd(data->env, data->export, data->bloc_lst[(*cmd)->i]);
	else if (str_is_equal((*cmd)->command[0], "pwd"))
		pwd();
	else if (str_is_equal((*cmd)->command[0], "export"))
		export(data, data->bloc_lst[(*cmd)->i]);
	else if (str_is_equal((*cmd)->command[0], "unset"))
		unset(data, data->bloc_lst[(*cmd)->i]);
	else if (str_is_equal((*cmd)->command[0], "env"))
		env(data->env, data->bloc_lst[(*cmd)->i]);
	else if (str_is_equal((*cmd)->command[0], "exit"))
		ft_exit(data, cmd, head);
}

void	exec_builtin(t_cmd **head, t_cmd **cmd, t_data *data, pid_t *last_pid)
{
	pid_t	pid;
	t_sig	*sig;

	do_pipe((*cmd)->pfd);
	pid = do_fork((*cmd)->pfd);
	if ((*cmd)->last && pid != 0)
		*last_pid = pid;
	if (pid == 0)
	{
		exec_builtin_func(head, cmd, data, pid);
		close_fds((*cmd)->pfd);
		free_commands(data, head);
		free_data(data);
		sig = get_sig();
		exit(sig->status);
	}
	dup2((*cmd)->pfd[0], STDIN_FILENO);
	close_fds((*cmd)->pfd);
}
