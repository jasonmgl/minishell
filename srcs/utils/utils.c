/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:32:39 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 01:05:02 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_set(char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	count_char(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
		if (line[i++] == c)
			count++;
	return (count);
}

int	str_is_equal(char *a, char *b)
{
	size_t	len_a;
	size_t	len_b;
	size_t	len_max;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	len_max = max(len_a, len_b);
	return (ft_strncmp(a, b, len_max) == 0);
}

size_t	max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}
