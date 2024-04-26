/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:19:52 by rsequeir          #+#    #+#             */
/*   Updated: 2024/04/26 14:49:15 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_array_length(char **array)
{
	size_t	length;

	length = 0;
	while (array && array[length])
		length++;
	return (length);
}

void	join_command(t_cmd **cmd, char *str)
{
	size_t	length;
	size_t	i;
	char	**new_array;

	length = get_array_length((*cmd)->command);
	new_array = ft_calloc((length + 2), sizeof(char *));
	i = 0;
	while (i < length)
	{
		new_array[i] = ft_strdup((*cmd)->command[i]);
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	free_split((*cmd)->command);
	(*cmd)->command = new_array;
}

void	parse_token(t_token *token, t_cmd **cmd)
{

	if (token->type == H_DOC)
	{
		(*cmd)->fd_infile = -1;
		(*cmd)->here_doc = 1;
	}
	else if (token->type == INFILE)
	{
		(*cmd)->fd_infile = -1;
		(*cmd)->infile = token->data;
	}
	else if (token->type == OUTFILE)
	{
		(*cmd)->fd_outfile = -1;
		(*cmd)->outfile = token->data;
	}
	else if (token->type == STDOUT || token->type == A_STDOUT)
		(*cmd)->append = token->type == A_STDOUT;
	else if (token->type == CMD || token->type == PARAM)
		join_command(cmd, token->data);
	else if (token->type == DELIMITER)
		(*cmd)->delimiter = token->data;
	else if (token->type == BUILTIN)
	{
		(*cmd)->builtin = 1;
		join_command(cmd, token->data);
	}
}

void    parse_command(t_token *token, t_cmd **cmd)
{
    t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		parse_token(tmp, cmd);
		tmp = tmp->next;
	}
}

void	do_heredoc(t_cmd **cmd, int first, int fd_stdin)
{
	pid_t	pid;

	do_pipe((*cmd)->pipe_fd);
	if (!first)
		dup2(fd_stdin, STDIN_FILENO);
	pid = do_fork((*cmd)->pipe_fd);
	if (pid == 0)
		read_lines(cmd);
	dup2((*cmd)->pipe_fd[0], STDIN_FILENO);
	close_fds((*cmd)->pipe_fd);
	wait(NULL);
}

void	do_open_infile(t_cmd **cmd)
{
	if ((*cmd)->fd_infile)
	{
		(*cmd)->fd_infile = open_infile((*cmd)->infile, (*cmd)->pipe_fd);
		if ((*cmd)->fd_infile)
		{
			close_fds((*cmd)->pipe_fd);
			exit(ERR);
		}
	}
}

void	do_open_outfile(t_cmd **cmd, int last)
{
	if ((*cmd)->fd_outfile)
	{
		if (open_outfile((*cmd)->outfile, (*cmd)->pipe_fd, (*cmd)->append))
		{
			close_fds((*cmd)->pipe_fd);
			exit(ERR);
		}
	}
	else if (!last)
		dup2((*cmd)->pipe_fd[1], STDOUT_FILENO);
}

void	open_files(t_cmd **cmd, int last)
{
	do_open_infile(cmd);
	do_open_outfile(cmd, last);
}

void	do_execve(t_cmd **cmd, int last)
{
	char	*command;
	
	open_files(cmd, last);
	close_fds((*cmd)->pipe_fd);
	command = get_command_path((*cmd)->command[0], (*cmd)->env);
	if (command && execve(command, (*cmd)->command, (*cmd)->env) == -1)
		print_strerror();
	free(command);
	free_split((*cmd)->command);
	exit(ERR);
}

int	str_is_equal(char *a, char *b)
{
	size_t	len_a;
	size_t	len_b;
	size_t	len_max;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	len_max = max(len_a, len_b);
	return (ft_strncmp(a, b, len_max) == 0);
}

void	exec_single_builtin(t_cmd **cmd, int last)
{
	open_files(cmd, last);
	if (str_is_equal((*cmd)->command[0], "echo"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "cd"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "pwd"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "export"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "unset"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "env"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "exit"))
		(void)0;
}

void	exec_builtin_func(t_cmd **cmd, int last)
{
	open_files(cmd, last);
	if (str_is_equal((*cmd)->command[0], "echo"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "cd"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "pwd"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "export"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "unset"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "env"))
		(void)0;
	else if (str_is_equal((*cmd)->command[0], "exit"))
		(void)0;
	exit(ERR);
}

void	exec_builtin(t_cmd **cmd, int last)
{
	pid_t	pid;

	do_pipe((*cmd)->pipe_fd);
	pid = do_fork((*cmd)->pipe_fd);
	if (pid == 0)
		exec_builtin_func(cmd, last);
	dup2((*cmd)->pipe_fd[0], STDIN_FILENO);
	close_fds((*cmd)->pipe_fd);
}

void	exec_command(t_cmd **cmd, int last, pid_t *last_pid, pid_t *pid)
{
	//pid_t	pid;
	t_sig	*sig;

	do_pipe((*cmd)->pipe_fd);
	sig = get_sig();
	if (str_is_equal((*cmd)->command[0], "./minishell"))
		sig->listen = 0;
	*pid = do_fork((*cmd)->pipe_fd);
	if (last && *pid != 0)
		*last_pid = *pid;
	if (*pid == 0)
		do_execve(cmd, last);
	dup2((*cmd)->pipe_fd[0], STDIN_FILENO);
	close_fds((*cmd)->pipe_fd);
}

void	free_commands(t_data data, t_cmd **cmd)
{
	size_t	i;
	
	if (cmd)
	{
		i = 0;
		while (i < data.nbr_cmd)
		{
			if (cmd[i])
			{
				if (cmd[i]->command)
					free_split(cmd[i]->command);
				free(cmd[i]);
			}
			i++;
		}
		free(cmd);
	}
}

size_t	get_lst_size(t_envp *env)
{
	t_envp	*tmp;
	size_t	n;

	tmp = env;
	n = 0;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

char	*free_strs(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*ft_strjoinf(char *s1, char *s2)
{
	size_t	ss1;
	size_t	ss2;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (free_strs(s1, s2));
	ss1 = ft_strlen(s1);
	ss2 = ft_strlen(s2);
	str = ft_calloc(ss1 + ss2 + 1, sizeof(char));
	if (str == NULL)
		return (free_strs(s1, s2));
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	free(s1 - ss1);
	free(s2 - ss2);
	return (str - ss1 - ss2);
}

char	*join_name_and_value(t_envp *env)
{
	char	*str;
	
	str = ft_strjoinf(ft_strdup(env->name), ft_strdup("="));
	str = ft_strjoinf(str, ft_strdup(env->value));
	return (str);
}

char	**free_envp(char **env, size_t i)
{
	while (i >= 0)
		free(env[i--]);
	free(env);
	return (NULL);
}

char	**t_envp_to_array(t_envp *env)
{
	size_t	n;
	size_t	i;
	char	**envp;
	t_envp	*tmp;

	n = get_lst_size(env);
	envp = ft_calloc((n + 1), sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (i < n)
	{
		envp[i] = ft_calloc(1, sizeof(char));
		envp[i] = join_name_and_value(tmp);
		if (envp[i] == NULL)
			return (free_envp(envp, i));
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	initialize_commands(t_cmd ***cmd, t_data data)
{
	size_t	i;
	
	*cmd = ft_calloc(data.nbr_cmd + 1, sizeof(t_cmd *));
	if (*cmd == NULL)
		return (ERR);
	i = 0;
	while (i < data.nbr_cmd)
	{
		(*cmd)[i] = ft_calloc(1, sizeof(t_cmd));
		if ((*cmd)[i] == NULL)
			return (ERR);
		(*cmd)[i]->env = t_envp_to_array(data.env);
		if ((*cmd)[i]->env == NULL)
			return (ERR);
		(*cmd)[i]->command = ft_calloc(1, sizeof(char *));
		if ((*cmd)[i]->command == NULL)
			return (ERR);
		parse_command(data.bloc_lst[i], &(*cmd)[i]);
		i++;
	}
	(*cmd)[i] = NULL;
	return (SUCCESS);
}

int	single_builtin(t_data data, t_cmd *cmd)
{
	return (data.nbr_cmd == 1 && cmd->builtin);
}

void	save_std_fd(int *fd_stdin, int *fd_stdout)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
}

void	restore_std_fd(int fd_stdin, int fd_stdout)
{
	dup2(fd_stdin, STDIN_FILENO);
	dup2(fd_stdout, STDOUT_FILENO);
}

int	has_heredoc(t_data data, t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while (i < data.nbr_cmd)
	{
		if (cmd[i++]->here_doc)
			return (1);
	}
	return (0);
}

void	exec_heredoc(t_data data, t_cmd **cmd, int fd_stdin)
{
	size_t	i;

	i = 0;
	while (i < data.nbr_cmd)
	{
		if (cmd[i]->here_doc)
		{
			cmd[i]->infile = create_tmp_file();
			do_heredoc(&cmd[i], i == 0, fd_stdin);
		}
		i++;
	}
}

void	exec_commands(t_data data, t_cmd **cmd, pid_t *last_pid, pid_t *pid)
{
	size_t	i;

	i = 0;
	while (i < data.nbr_cmd)
	{
		if (cmd[i]->builtin)
			exec_builtin(&cmd[i], i == (data.nbr_cmd - 1));
		else
			exec_command(&cmd[i], i == (data.nbr_cmd - 1), last_pid, pid);
		i++;
	}
}

void	delete_tmp_files(t_data data, t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while (i < data.nbr_cmd)
	{
		if (cmd[i]->here_doc)
			unlink(cmd[i]->infile);
		i++;
	}
}

void	exec_pipeline(t_data data, t_cmd **cmd, int fd_stdin)
{
	t_sig	*sig;
	pid_t	last_pid;
	pid_t	pid;
	int		heredoc;
	int		status;
	int		signaled;
	
	sig = get_sig();
	status = 0;
	signaled = 0;
	last_pid = 0;
	heredoc = has_heredoc(data, cmd);
	if (heredoc)
	{
		sig->heredoc = 1;
		exec_heredoc(data, cmd, fd_stdin);
	}
	exec_commands(data, cmd, &last_pid, &pid);
	if (wait(&status) == -1)
		printf("pid: %d - %s\n", pid, strerror(errno));
	if (heredoc)
		delete_tmp_files(data, cmd);
}

int	execute_all(t_data data)
{
    t_cmd   **cmd;
	int		fd_stdin;
	int		fd_stdout;
	t_sig	*sig;

	if (initialize_commands(&cmd, data) == ERR)
		return (ERR);
	sig = get_sig();
	sig->work = 1;
	save_std_fd(&fd_stdin, &fd_stdout);
	if (single_builtin(data, cmd[0]))
		exec_single_builtin(&cmd[0], 1);
	else
		exec_pipeline(data, cmd, fd_stdin);
	restore_std_fd(fd_stdin, fd_stdout);
	sig->work = 0;
	sig->listen = 1;
	return (SUCCESS);
}
