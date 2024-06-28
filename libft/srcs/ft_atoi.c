/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:34:23 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/05 22:01:08 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	size_t			i;
	long long		nbr;
	unsigned int	count;

	i = 0;
	nbr = 0;
	count = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			count++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nbr != ((nbr * 10) + (nptr[i] - 48)) / 10)
			return (count - 1);
		nbr = (nbr * 10) + (nptr[i] - 48);
		i++;
	}
	if (count != 0)
		return ((int)(nbr * -1));
	return ((int)nbr);
}
