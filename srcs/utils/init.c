/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:50:19 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 15:22:22 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env_lst(char *envp[], t_data *data)
{
	size_t	i;

	if (!data)
		return (0);
	i = 0;
	while (envp[i])
	{
		extract_var_env(envp[i], &data->env);
		extract_var_env(envp[i], &data->export);
		i++;
	}
	return (1);
}

int	init_struct(t_data *data, char *envp[])
{
	if (!envp)
		return (0);
	if (!data->envp)
	{
		data->envp = envp;
		if (!init_env_lst(envp, data))
			return (0);
	}
	return (1);
}
