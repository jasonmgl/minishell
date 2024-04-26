/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:21:56 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	free_res_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	nbr_word;
	size_t	in_word;

	i = 0;
	in_word = 0;
	nbr_word = 0;
	while (s[i])
	{
		if (in_word == 1 && s[i] == c)
			in_word = 0;
		else if (in_word == 0 && s[i] != c)
		{
			in_word = 1;
			nbr_word++;
		}
		else
			i++;
	}
	return (nbr_word);
}

static char	**ex_word(char const *s, size_t nbr_word, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (i < nbr_word)
	{
		while (s[j] && s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		tab[i] = ft_substr(s, start, (j - start));
		if (!tab[i])
		{
			free_res_tab(tab);
			return (NULL);
		}
		i++;
	}
	tab[nbr_word] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	nbr_word;
	char	**tab;

	if (!s)
		return (NULL);
	nbr_word = count_word((char *)s, c);
	tab = malloc(sizeof(char *) * (nbr_word + 1));
	if (!tab)
		return (NULL);
	return (ex_word(s, nbr_word, c, tab));
}
