/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:21:03 by rsequeir          #+#    #+#             */
/*   Updated: 2024/04/16 19:26:02 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	size;
	size_t	size_s1;
	char	*str;

	size_s1 = ft_strlen(s1);
	size = size_s1 + ft_strlen(s2);
	str = (char *) malloc((size + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	s1 = s1 - size_s1;
	free(s1);
	return (str - size);
}
