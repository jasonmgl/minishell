/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:50:19 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 15:55:47 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_data *data, char *envp[])
{
	size_t	i;

	i = 0;
	ft_memset(data, 0, sizeof(t_data));
	data->envp = envp;
	data->fd_stdin = -1;
	data->fd_stdout = -1;
	while (envp[i])
	{
		add_venv_to_env(envp[i], &data->env);
		if (add_venv_to_export(envp[i], &data->export) == ERR)
		{
			error_handler("Error : unable to initialize environment: ");
			strerror(errno);
			free_data(data);
			return (ERR);
		}
		i++;
	}
	return (SUCCESS);
}
