/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:21:01 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static unsigned int	count_char(int n)
{
	unsigned int	count;

	count = 0;
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	count++;
	return (count);
}

static char	*convert(char *str, int n, unsigned int isneg, unsigned int count)
{
	unsigned int	i;

	i = count - 1;
	str[count] = '\0';
	if (isneg == 1)
		str[0] = '-';
	while (n > 9)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	str[i] = n + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	count;
	unsigned int	isneg;
	char			*str;

	count = 0;
	isneg = 0;
	if (n == -2147483648)
	{
		str = ft_substr("-2147483648", 0, 11);
		return (str);
	}
	if (n < 0)
	{
		count++;
		isneg++;
		n = (n * -1);
	}
	count = count + count_char(n);
	str = ft_calloc((count + 1), 1);
	if (!str)
		return (NULL);
	return (convert(str, n, isneg, count));
}
