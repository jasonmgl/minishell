/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:14:33 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		i;

	i = 0;
	if (!s[i] || !s || start > ft_strlen(s) || len == 0)
	{
		ptr = ft_calloc(1, 1);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s + start);
	ptr = ft_calloc((len + 1), 1);
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
