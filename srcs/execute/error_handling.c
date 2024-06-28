/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:47:12 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/05 18:44:59 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strerror(void)
{
	char	*str;

	str = ft_strdup(strerror(errno));
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, "\n");
	if (str == NULL)
		return ;
	ft_putstr_fd(str, 2);
	free(str);
}

void	print_file_error(char *file)
{
	char	*str;

	str = ft_strdup(strerror(errno));
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, ": ");
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, file);
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, "\n");
	if (str == NULL)
		return ;
	ft_putstr_fd(str, 2);
	free(str);
}

void	print_command_not_found(char *command)
{
	char	*str;

	str = ft_strdup("command not found: ");
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, command);
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, "\n");
	if (str == NULL)
		return ;
	ft_putstr_fd(str, 2);
	free(str);
}

void	print_permission_denied(char *arg)
{
	char	*str;

	str = ft_strdup("permission denied: ");
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, arg);
	if (str == NULL)
		return ;
	str = ft_strjoin_free(str, "\n");
	if (str == NULL)
		return ;
	ft_putstr_fd(str, 2);
	free(str);
}
