/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:37:38 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;

	i = ft_strlen((char *)s) + 1;
	while (i-- > 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
	}
	return ((char *) NULL);
}
