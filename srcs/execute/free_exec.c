/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:02:57 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 11:38:30 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_commands_content(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->command)
			free_split(cmd->command);
		if (cmd->env)
			free_split(cmd->env);
		if (cmd->outs)
			free_split(cmd->outs);
		if (cmd->delimiters)
			free_split(cmd->delimiters);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
	}
}

void	free_commands(t_data *data, t_cmd **cmd)
{
	size_t	i;

	if (cmd)
	{
		i = 0;
		while (i < data->nbr_cmd)
		{
			if (cmd[i])
				free_commands_content(cmd[i]);
			i++;
		}
		free(cmd);
	}
}
