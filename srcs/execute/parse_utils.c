/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:32:07 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/13 13:36:34 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_heredoc(t_token *token, t_cmd **cmd)
{
	if (token->type == H_DOC)
	{
		(*cmd)->fd_in = -1;
		(*cmd)->here_doc++;
	}
}

static int	parse_redir(t_token *token, t_cmd **cmd)
{
	parse_heredoc(token, cmd);
	if (token->type == INFILE)
	{
		(*cmd)->fd_in = -1;
		(*cmd)->infile = ft_strdup(token->data);
		if ((*cmd)->infile == NULL)
			return (ERR);
	}
	else if (token->type == OUTFILE)
	{
		(*cmd)->fd_out = -1;
		if ((*cmd)->outfile)
			free((*cmd)->outfile);
		(*cmd)->outfile = ft_strdup(token->data);
		if ((*cmd)->outfile == NULL)
			return (ERR);
		if (append(&(*cmd)->outs, token->data) == ERR)
			return (ERR);
	}
	else if (token->type == STDOUT || token->type == A_STDOUT)
		(*cmd)->append = token->type == A_STDOUT;
	else if (token->type == DELIMITER)
		if (append(&(*cmd)->delimiters, token->data) == ERR)
			return (ERR);
	return (SUCCESS);
}

size_t	get_array_length(char **array)
{
	size_t	length;

	length = 0;
	while (array && array[length])
		length++;
	return (length);
}

int	append(char ***array, char *str)
{
	size_t	length;
	size_t	i;
	char	**new_array;

	length = get_array_length(*array);
	new_array = ft_calloc((length + 2), sizeof(char *));
	if (new_array == NULL)
		return (ERR);
	i = 0;
	while (i < length)
	{
		new_array[i] = ft_strdup((*array)[i]);
		if (new_array[i++] == NULL)
		{
			free_split(new_array);
			return (ERR);
		}
	}
	new_array[i] = ft_strdup(str);
	if (new_array[i] == NULL)
		return (ERR);
	new_array[i + 1] = NULL;
	free_split(*array);
	*array = new_array;
	return (SUCCESS);
}

int	parse_token(t_token *token, t_cmd **cmd)
{
	if (parse_redir(token, cmd) == ERR)
		return (ERR);
	if (token->type == CMD || token->type == PARAM)
	{
		if (append(&(*cmd)->command, token->data) == ERR)
			return (ERR);
	}
	else if (token->type == BUILTIN)
	{
		(*cmd)->builtin = 1;
		if (append(&(*cmd)->command, token->data) == ERR)
			return (ERR);
	}
	return (SUCCESS);
}
