/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:09:47 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define BASE_X16 "0123456789ABCDEF"
#define BASE_16 "0123456789abcdef"

int	ft_putchar_printf(int c, size_t *ptr)
{
	*ptr += 1;
	return (write(1, &c, 1));
}

int	ft_putstr_printf(char *str, size_t *ptr)
{
	if (!str)
	{
		*ptr += 6;
		return (write(1, "(null)", 6));
	}
	*ptr += ft_strlen(str);
	return (write(1, str, ft_strlen(str)));
}

void	ft_putnbr_printf(int n, size_t *ptr)
{
	if (n == -2147483648)
		ft_putstr_printf("-2147483648", ptr);
	else if (n >= 0 && n <= 9)
		ft_putchar_printf((48 + n), ptr);
	else if (n > 9)
	{
		ft_putnbr_printf(n / 10, ptr);
		ft_putnbr_printf(n % 10, ptr);
	}
	else if (n < 0)
	{
		ft_putchar_printf('-', ptr);
		ft_putnbr_printf(-n, ptr);
	}
}

void	ft_putunbr_printf(size_t n, size_t *ptr)
{
	if (n <= 9)
		ft_putchar_printf((48 + n), ptr);
	else if (n > 9)
	{
		ft_putunbr_printf(n / 10, ptr);
		ft_putunbr_printf(n % 10, ptr);
	}
}

void	ft_puthex_printf(size_t n, size_t x, size_t *ptr)
{
	char	*str;

	if (x == 1)
		str = BASE_X16;
	else if (x == 2)
	{
		if (!n)
		{
			ft_putstr_printf("(nil)", ptr);
			return ;
		}
		ft_putstr_printf("0x", ptr);
		x = 0;
	}
	if (x == 0)
		str = BASE_16;
	if (n > 15)
	{
		ft_puthex_printf(n / 16, x, ptr);
		ft_puthex_printf(n % 16, x, ptr);
	}
	else
		ft_putchar_printf(str[n], ptr);
}
