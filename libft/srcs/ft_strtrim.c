/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:08:23 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	loop_i(char const *s1, char const *set)
{
	size_t		i;
	int			i_set;

	i = 0;
	i_set = 0;
	while (set[i_set])
	{
		if (s1[i] == set[i_set])
		{
			i_set = -1;
			i++;
		}
		i_set++;
	}
	return (i);
}

static size_t	loop_j(char const *s1, char const *set)
{
	size_t		j;
	int			i_set;

	j = (ft_strlen(s1) - 1);
	i_set = 0;
	while (set[i_set])
	{
		if (s1[j] == set[i_set])
		{
			i_set = -1;
			j--;
		}
		i_set++;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ptr;
	size_t		i;
	size_t		j;

	i = loop_i(s1, set);
	j = loop_j(s1, set);
	ptr = ft_substr(s1, i, ((j - i) + 1));
	return (ptr);
}
