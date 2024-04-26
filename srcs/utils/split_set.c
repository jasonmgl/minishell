/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:51:26 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 14:56:50 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_res_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

static bool	is_set(char *set, char c)
{
	size_t	i;

	if (!set || !c)
		return (false);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static size_t	count_word(char *s, char *set)
{
	bool			in_word;
	size_t			nbr_word;
	size_t			i;
	
	i = 0;
	nbr_word = 0;
	in_word = false;
	while (s[i])
	{
		if (s[i] && is_set(set, s[i]))
		{
			i++;
			nbr_word++;
		}
		else if (s[i] && !is_set(set, s[i]))
			nbr_word++;
		while (s[i] && !is_set(set, s[i]))
			i++;
	}
	return (nbr_word);
}


static char	**ex_word(char const *s, char *set, char **tab, size_t nbr_word)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[j] && is_set(set, s[j]))
			j++;
		while (s[j] && !is_set(set, s[j]))
			j++;
		tab[k] = ft_substr(s, i, (j - i));
		if (!tab[k++])
			return (free_res_tab(tab), NULL);
		i = j;
	}
	tab[nbr_word] = NULL;
	return (tab);
}


char	**ft_split_set(char *s, char *set)
{
	size_t	nbr_word;
	char	**tab;

	if (!s || !set)
		return (NULL);
	nbr_word = count_word((char *)s, set);
	tab = ft_calloc((nbr_word + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	return (ex_word(s, set, tab, nbr_word));
}
