/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:23:53 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 15:11:27 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_word(t_token **lst, const char *line, int *i)
{
	char	*buf;
	int		len;
	t_token	*lst_new;

	if (!line)
		return (0);
	lst_new = NULL;
	if (find_quote(line))
		len = len_word_in_quotes(line, find_quote(line));
	else
		len = len_word_with_set(line, "|<> ");
	buf = ft_calloc(len + 1, sizeof(char));
	if (!buf)
		return (0);
	ft_strlcpy(buf, line, len + 1);
	lst_new = token_lstnew(buf, WORD);
	if (!lst_new)
		return (0);
	token_lstadd_back(lst, lst_new);
	*i += len;
	return (1);
}

static int	extract_op(t_token **lst, char *str, t_redir type, int *i)
{
	char	*buf;
	t_token	*lst_new;

	if (!str)
		return (0);
	buf = ft_strdup(str);
	if (!buf)
		return (0);
	lst_new = token_lstnew(buf, type);
	if (!lst_new)
		return (0);
	token_lstadd_back(lst, lst_new);
	*i += ft_strlen(buf);
	return (1);
}

static int	extract_r_chevron(t_token **lst, char *line, int *i)
{
	if (line[1] == '>')
		return (extract_op(lst, ">>", A_STDOUT, i));
	else
		return (extract_op(lst, ">", STDOUT, i));
}

static int	extract_l_chevron(t_token **lst, char *line, int *i)
{
	if (line[1] == '<')
		return (extract_op(lst, "<<", H_DOC, i));
	else
		return (extract_op(lst, "<", STDIN, i));
}

t_token	*tokeniser(char *line)
{
	t_token	*lst;
	int		i;
	int		verif;

	if (!line)
		return (NULL);
	i = 0;
	lst = NULL;
	verif = 0;
	while (line[i] && line)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '<')
			verif = extract_l_chevron(&lst, &line[i], &i);
		else if (line[i] == '>')
			verif = extract_r_chevron(&lst, &line[i], &i);
		else if (line[i] == '|')
			verif = extract_op(&lst, "|", PIPE, &i);
		else if (line[i] != ' ' && line[i])
			verif = extract_word(&lst, &line[i], &i);
		if (verif == 0)
			return (NULL);
	}
	return (lst);
}
