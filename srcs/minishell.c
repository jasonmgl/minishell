/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:36:30 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 16:05:09 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	show_prompt(char **line)
{
	if (isatty(1))
	{
		*line = readline(PROMPT);
		if (*line == NULL)
			return (ERR);
	}
	else
	{
		*line = readline("");
		if (*line == NULL)
			return (ERR);
	}
	return (SUCCESS);
}

void	free_before_next_prompt(t_data *data)
{
	if (data->lst)
	{
		free_lst_token(data->lst);
		data->lst = NULL;
	}
	if (data->bloc_lst)
	{
		free_bloc_lst_token(data->bloc_lst);
		if (data->bloc_lst)
		{
			free(data->bloc_lst);
			data->bloc_lst = NULL;
		}
	}
}

int	add_input_to_history(char *line)
{
	size_t	i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isspace(line[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	user_input(t_data *data, char *line)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_on_new_line();
	if (show_prompt(&line) == ERR)
		return (ERR);
	if (add_input_to_history(line))
		add_history(line);
	if (parser(data, line) == SUCCESS)
		execute_all(data);
	free_before_next_prompt(data);
	return (SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	data;
	t_sig	*sig;

	if (init_env(&data, envp) == ERR)
		return (ERR);
	line = NULL;
	init_sig();
	sig = get_sig();
	if (argc == 1 && argv)
	{
		while (user_input(&data, line) == SUCCESS)
			(void) "wait for next user input...";
		free(line);
		write(1, "exit\n", 5);
		free_data(&data);
		rl_clear_history();
		return (sig->status);
	}
	return (sig->status);
}
