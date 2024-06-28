/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:06:14 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 00:02:22 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_command(t_token *token, t_cmd **cmd)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (parse_token(tmp, cmd) == ERR)
			return (ERR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static int	allocate_command_memory(t_cmd **cmd)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (*cmd == NULL)
		return (ERR);
	(*cmd)->command = ft_calloc(1, sizeof(char *));
	(*cmd)->outs = ft_calloc(1, sizeof(char *));
	(*cmd)->delimiters = ft_calloc(1, sizeof(char *));
	if (((*cmd)->command == NULL) || ((*cmd)->outs == NULL) || \
	((*cmd)->delimiters == NULL))
		return (ERR);
	return (SUCCESS);
}

int	initialize_commands(t_cmd ***cmd, t_data *data)
{
	size_t	i;

	*cmd = ft_calloc(data->nbr_cmd + 1, sizeof(t_cmd *));
	if (*cmd == NULL)
		return (ERR);
	i = 0;
	while (i < data->nbr_cmd)
	{
		if (allocate_command_memory(&(*cmd)[i]) == ERR)
			return (ERR);
		(*cmd)[i]->env = t_envp_to_array(data->env);
		if ((*cmd)[i]->env == NULL)
			return (ERR);
		if (parse_command(data->bloc_lst[i], &(*cmd)[i]) == ERR)
			return (ERR);
		(*cmd)[i]->i = i;
		(*cmd)[i]->last = i == (data->nbr_cmd - 1);
		i++;
	}
	(*cmd)[i] = NULL;
	return (SUCCESS);
}
