/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:46:27 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/04 02:46:45 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
}
