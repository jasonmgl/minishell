/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:19:52 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/13 18:12:35 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_execve(t_cmd **head, t_cmd **cmd, t_data *data, pid_t pid)
{
	char		*command;
	int			status;
	struct stat	buf;

	status = 0;
	open_files(data, head, cmd, pid);
	close_fds((*cmd)->pfd);
	command = get_command_path((*cmd)->command[0], (*cmd)->env, &status);
	if (command && execve(command, (*cmd)->command, (*cmd)->env) == -1)
	{
		stat(command, &buf);
		if (S_ISDIR(buf.st_mode))
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		else
			print_strerror();
	}
	free(command);
	free_commands(data, head);
	free_data(data);
	exit(status);
}

static void	exec_command(t_cmd **head, t_cmd **cmd, t_data *data, pid_t *last)
{
	pid_t	pid;
	t_sig	*sig;

	sig = get_sig();
	if (sig->sigint == 0)
	{
		do_pipe((*cmd)->pfd);
		signal(SIGINT, signal_child_handler);
		signal(SIGQUIT, signal_child_handler);
		pid = do_fork((*cmd)->pfd);
		if ((*cmd)->last && pid != 0)
			*last = pid;
		if (pid == 0)
			do_execve(head, cmd, data, pid);
		dup2((*cmd)->pfd[0], STDIN_FILENO);
		close_fds((*cmd)->pfd);
	}
}

static void	wait_execution(pid_t last)
{
	t_sig	*sig;
	pid_t	pid;
	int		status;

	sig = get_sig();
	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == last)
		{
			if (WIFEXITED(status))
				sig->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig->status = WTERMSIG(status) + 128;
				if (WTERMSIG(status) == SIGINT)
					write(STDERR_FILENO, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					write(STDERR_FILENO, "Quit (core dumped)\n", 19);
			}
		}
		pid = wait(&status);
	}
}

static void	exec_pipeline(t_data *data, t_cmd **cmd)
{
	pid_t	last_pid;
	size_t	i;
	int		heredoc;
	t_sig	*sig;

	last_pid = 0;
	sig = get_sig();
	heredoc = has_heredoc(data, cmd);
	if (heredoc)
		exec_heredoc(data, cmd);
	i = 0;
	while (i < data->nbr_cmd)
	{
		sig->i = i;
		if (cmd[i]->builtin)
			exec_builtin(cmd, &cmd[i], data, &last_pid);
		else if (cmd[i]->command[0])
			exec_command(cmd, &cmd[i], data, &last_pid);
		i++;
	}
	wait_execution(last_pid);
	if (heredoc)
		delete_tmp_files(data, cmd);
}

int	execute_all(t_data *data)
{
	t_cmd	**cmd;
	t_sig	*sig;

	sig = get_sig();
	if (initialize_commands(&cmd, data) == ERR)
		return (ERR);
	add_struct_to_sig(data, cmd);
	save_std_fd(data);
	if (single_builtin(data, cmd[0]))
		exec_builtin_func(cmd, &cmd[0], data, 1);
	else
		exec_pipeline(data, cmd);
	restore_std_fd(data);
	free_commands(data, cmd);
	if (sig->sigint == 1)
		sig->sigint = 0;
	return (SUCCESS);
}
