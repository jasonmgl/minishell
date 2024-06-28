/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:19:02 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 01:04:06 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_in_quote(char *line, char **new, t_quotes *quotes)
{
	while (line[quotes->i] && line[quotes->i] != quotes->quote)
		(*new)[quotes->j++] = line[quotes->i++];
	if (line[quotes->i] && line[quotes->i] == quotes->quote)
	{
		quotes->quote = '\0';
		quotes->in_quote = false;
		quotes->i++;
	}
}

static void	remove_out_quote(char *line, char **new, t_quotes *quotes)
{
	while (line[quotes->i] && line[quotes->i] != '\'' && line[quotes->i] != '"')
		(*new)[quotes->j++] = line[quotes->i++];
	if (line[quotes->i] && (line[quotes->i] == '\'' || line[quotes->i] == '"'))
	{
		if (line[quotes->i] == '"')
			quotes->quote = '"';
		else
			quotes->quote = '\'';
		quotes->in_quote = true;
		quotes->i++;
	}
}

static void	get_line_without_quotes(char *line, char **new, size_t size)
{
	t_quotes	quotes;

	quotes.in_quote = false;
	quotes.quote = '\0';
	quotes.i = 0;
	quotes.j = 0;
	while (line[quotes.i] && quotes.j < size)
	{
		if (quotes.in_quote == true)
			remove_in_quote(line, new, &quotes);
		else
			remove_out_quote(line, new, &quotes);
		if (line[quotes.i] && line[quotes.i] == quotes.quote && \
		quotes.in_quote == true)
		{
			quotes.in_quote = false;
			quotes.quote = '\0';
			quotes.i++;
		}
	}
	(*new)[quotes.j] = '\0';
}

char	*remove_quotes(char *line)
{
	char	*new;
	size_t	size;

	size = ft_strlen(line);
	new = ft_calloc((size + 1), sizeof(char));
	if (new == NULL)
		return (NULL);
	get_line_without_quotes(line, &new, size);
	free(line);
	return (new);
}
