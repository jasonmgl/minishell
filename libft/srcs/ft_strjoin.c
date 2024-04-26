/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:25:43 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_newstr(char *p_s1, char *p_s2, char *p_new)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (p_s1[i])
	{
		p_new[j] = p_s1[i];
		i++;
		j++;
	}
	i = 0;
	while (p_s2[i])
	{
		p_new[j] = p_s2[i];
		i++;
		j++;
	}
	p_new[j] = '\0';
	return (p_new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len_s1;
	size_t		len_s2;
	char		*p_new;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p_new = malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (!p_new)
		return (NULL);
	return (ft_newstr((char *)s1, (char *)s2, p_new));
}
