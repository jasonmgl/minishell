/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_into_lst_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:57:27 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 13:30:34 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	len_word_with_set(const char *line, const char *set_char)
{
	int	i;
	int	j;

	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (line[i])
	{
		while (set_char[j])
			if (line[i] == set_char[j++])
				return (i);
		j = 0;
		i++;
	}
	return (i);
}

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

void	utils_check_quotes(char c, t_check_quotes *check)
{
	if (c == '\'')
	{
		if (!check->in_d_quote)
		{
			check->s_quote++;
			if (check->in_s_quote)
				check->in_s_quote = false;
			else
				check->in_s_quote = true;
		}
	}
	else if (c == '"')
	{
		if (!check->in_s_quote)
		{
			check->d_quote++;
			if (check->in_d_quote)
				check->in_d_quote = false;
			else
				check->in_d_quote = true;
		}
	}
}
