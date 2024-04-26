/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:35:50 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:52 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_argmnts(va_list args, char c, size_t *ptr)
{
	int		verif;

	verif = 1;
	if (c == '%')
		verif = ft_putchar_printf('%', ptr);
	else if (c == 'c')
		verif = ft_putchar_printf(va_arg(args, int), ptr);
	else if (c == 's')
		verif = ft_putstr_printf((char *)va_arg(args, char *), ptr);
	else if (c == 'd')
		ft_putnbr_printf(va_arg(args, int), ptr);
	else if (c == 'i')
		ft_putnbr_printf(va_arg(args, int), ptr);
	else if (c == 'u')
		ft_putunbr_printf(va_arg(args, unsigned int), ptr);
	else if (c == 'x')
		ft_puthex_printf(va_arg(args, unsigned int), 0, ptr);
	else if (c == 'X')
		ft_puthex_printf(va_arg(args, unsigned int), 1, ptr);
	else if (c == 'p')
		ft_puthex_printf(va_arg(args, size_t), 2, ptr);
	else
		verif = -1;
	return (verif);
}

int	ft_printf(const char *str, ...)
{
	size_t		i;
	size_t		nbr;
	va_list		args;

	nbr = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_argmnts(args, str[++i], &nbr) == -1)
				return (-1);
			i++;
		}
		while (str[i] != '%' && str[i] != '\0')
		{
			ft_putchar_printf(str[i], &nbr);
			i++;
		}
	}
	va_end(args);
	return (nbr);
}
