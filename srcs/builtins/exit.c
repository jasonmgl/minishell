/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:49:43 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 16:22:29 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_numeric_arg(char *str)
{
	char	*new_str;

	new_str = ft_strdup("exit: ");
	if (!str)
		return (ERR);
	new_str = ft_strjoin_free(new_str, str);
	if (!str)
		return (ERR);
	new_str = ft_strjoin_free(new_str, ": numeric argument required\n");
	if (!str)
		return (ERR);
	ft_putstr_fd(new_str, 2);
	free(new_str);
	return (SUCCESS);
}

static int	cmd_has_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (SUCCESS);
		i++;
	}
	return (ERR);
}

void	check_and_set_status(t_cmd **cmd, unsigned char *status)
{
	long long	value_max;

	if (cmd_has_alpha((*cmd)->command[1]) == SUCCESS)
	{
		print_error_numeric_arg((*cmd)->command[1]);
		*status = 2;
	}
	else
	{
		value_max = ft_atoi((*cmd)->command[1]);
		if ((value_max == -1 && (*cmd)->command[1][0] != '-') || \
		(value_max == 0 && (*cmd)->command[1][0] == '-'))
		{
			print_error_numeric_arg((*cmd)->command[1]);
			*status = 2;
		}
		else
			*status = (unsigned char) ft_atoi((*cmd)->command[1]);
	}
}

void	ft_exit(t_data *data, t_cmd **cmd, t_cmd **head)
{
	t_sig			*sig;
	unsigned char	exit_status;

	sig = get_sig();
	exit_status = sig->status;
	if (data->nbr_cmd == 1)
		write(STDOUT_FILENO, "exit\n", 5);
	if ((*cmd)->command[1] && (*cmd)->command[2] == NULL)
		check_and_set_status(cmd, &exit_status);
	else if ((*cmd)->command[1] && (*cmd)->command[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_status = 1;
	}
	close_fds((*cmd)->pfd);
	free_commands(data, head);
	free_data(data);
	exit(exit_status);
}
