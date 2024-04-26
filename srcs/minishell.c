/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:36:30 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 18:26:03 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	data;
	t_sig	*sig;

	ft_memset(&data, 0, sizeof(t_data));
	line = NULL;
	if (argc == 1 && argv)
	{
		init_sig();
		while (1)
		{
			sig = get_sig();
			line = readline(PROMPT);
			if (!line)
			{
				write(1, "exit\n", 5);
				free_data(&data);
				rl_clear_history();
				exit(EXIT_SUCCESS);
				return (0);
			}
			add_history(line);
			if (parser(&data, line, envp))
				execute_all(data);
			rl_on_new_line();
		}
		free_data(&data);
		rl_clear_history();
		exit(EXIT_SUCCESS);
		return (0);
	}
	return (1);
}
