/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:34:31 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 00:26:10 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_not_valid_param(char c)
{
	return (c != 'n' && c != 'e' && c != 'E');
}

int	contain_nl_param(char *arg)
{
	int	i;
	int	n;

	if (arg && arg[0] != '-')
		return (0);
	n = 0;
	i = 1;
	while (arg && arg[i])
	{
		if (i > 0 && is_not_valid_param(arg[i]))
			return (0);
		if (arg[i] == 'n')
			n++;
		i++;
	}
	if (n > 0)
		return (1);
	else
		return (2);
	return (n > 0);
}

void	echo(char **args)
{
	t_sig	*sig;
	size_t	i;
	int		nl;

	sig = get_sig();
	if (args == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		sig->status = 0;
		return ;
	}
	nl = contain_nl_param(args[0]);
	i = 0 + (nl > 0);
	while (args && args[i])
	{
		if (i > (size_t)(0 + (nl > 0)))
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl != 1)
		write(STDOUT_FILENO, "\n", 1);
	sig->status = 0;
}
