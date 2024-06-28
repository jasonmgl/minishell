/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_into_lst_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:57:27 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/05 23:00:07 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_word(const char *line)
{
	int	count;

	if (!line)
		return (0);
	count = 0;
	while (line[count] != '|' && line[count] != '<'
		&& line[count] != '>' && line[count] != ' '
		&& line[count] != '\0')
		count++;
	return (count);
}

int	find_quote(const char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			return ('\'');
		else if (line[i] == '"')
			return ('"');
		if (line[i] == ' ' || line[i] == '<'
			|| line[i] == '>' || line[i] == '|')
			return (0);
		i++;
	}
	return (0);
}

size_t	get_first_match(char *str, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (set[j])
			if (str[i] == set[j++])
				return (i);
		i++;
	}
	return (i);
}

int	len_word_in_quotes(const char *line, int c)
{
	int		count;
	bool	in_quote;

	if (!line || c == 0)
		return (0);
	count = 0;
	in_quote = false;
	while (line[count] && line[count] != ' ' && !in_quote)
	{
		while (line[count] != c && line[count])
			count++;
		if (line[count])
			count++;
		in_quote = true;
		while (line[count] != c && line[count])
			count++;
		if (line[count])
			count++;
		in_quote = false;
		if (find_quote(&line[count]) && !in_quote)
			c = find_quote(&line[count]);
		else if (!find_quote(&line[count]) && !in_quote)
			return (count += len_word(&line[count]));
	}
	return (count);
}
