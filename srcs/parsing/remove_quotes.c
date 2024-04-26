/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:19:02 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 15:55:57 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_quotes_to_remove(char *line)
{
	t_check_quotes	check;
	size_t			count;
	size_t			i;

	if (!line)
		return (0);
	i = 0;
	count = 0;
	ft_memset(&check, 0, sizeof(t_check_quotes));
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"')
			&& !check.in_d_quote && !check.in_s_quote)
			count++;
		if (line[i] == '\'')
			utils_check_quotes(line[i], &check);
		else if (line[i] == '"')
			utils_check_quotes('"', &check);
		if ((line[i] == '\'' || line[i] == '"')
			&& !check.in_d_quote && !check.in_s_quote)
			count++;
		i++;
	}
	return (count);
}

static void	get_inside_s_quote(char *new_line, char *line, size_t *i, size_t *j)
{
	(*i)++;
	while (line[*i] != '\'' && line[*i])
	{
		if (line[*i] == '$' * -1)
			new_line[(*j)++] = line[(*i)++] * -1;
		else
			new_line[(*j)++] = line[(*i)++];
	}
	(*i)++;
}

static void	get_inside_d_quote(char *new_line, char *line, size_t *i, size_t *j)
{
	(*i)++;
	while (line[*i] != '"' && line[*i])
		new_line[(*j)++] = line[(*i)++];
	(*i)++;
}

static char	*replace(char *line)
{
	char	*new_line;
	size_t	len_without_quotes;
	size_t	i;
	size_t	j;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	len_without_quotes = ft_strlen(line) - count_quotes_to_remove(line);
	new_line = ft_calloc(len_without_quotes + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			get_inside_s_quote(new_line, line, &i, &j);
		else if (line[i] == '"')
			get_inside_d_quote(new_line, line, &i, &j);
		else
			new_line[j++] = line[i++];
	}
	return (new_line);
}

int	remove_quotes(t_token **bloc_lst)
{
	t_token	*ptr;
	char	*tmp;
	size_t	i;

	if (!bloc_lst || !*bloc_lst)
		return (0);
	i = 0;
	while (bloc_lst[i])
	{
		ptr = bloc_lst[i];
		while (ptr)
		{
			if (ft_strchr(ptr->data, '\'') || ft_strchr(ptr->data, '"'))
			{
				tmp = ptr->data;
				ptr->data = replace(ptr->data);
				free(tmp);
				if (!ptr->data)
					return (0);
			}
			ptr = ptr->next;
		}
		i++;
	}
	return (1);
}
