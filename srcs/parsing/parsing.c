/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:44:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 16:04:47 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_word(t_token *tmp, bool *cmd)
{
	if (tmp->prev->type == STDIN)
		tmp->type = INFILE;
	else if (tmp->prev->type == STDOUT || tmp->prev->type == A_STDOUT)
		tmp->type = OUTFILE;
	else if (tmp->prev->type == H_DOC)
		tmp->type = DELIMITER;
	else if (*cmd == false)
	{
		tmp->type = CMD;
		*cmd = true;
	}
	else
		tmp->type = PARAM;
}

void	edit_lst_type(t_token *lst)
{
	t_token	*tmp;
	bool	cmd;

	tmp = lst;
	cmd = false;
	while (tmp)
	{
		if (tmp->type == PIPE)
			cmd = false;
		else if (tmp->type == WORD && tmp->prev == NULL)
		{
			tmp->type = CMD;
			cmd = true;
		}
		else if (tmp->type == WORD)
			edit_word(tmp, &cmd);
		tmp = tmp->next;
	}
}

int	parser(t_data *data, char *line)
{
	if (check_syntax(data, line) == ERR)
		return (ERR);
	if (expand(data, &line, false) == ERR)
		return (ERR);
	if (line == NULL)
		return (ERR);
	data->lst = tokeniser(line);
	if (!data->lst)
		return (ERR);
	if (check_operator(data->lst) == ERR)
		return (ERR);
	if (lst_into_bloc(data, data->lst) == ERR)
		return (ERR);
	identify_builtins(data, data->bloc_lst);
	free(line);
	return (SUCCESS);
}
