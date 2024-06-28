/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:45:06 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 01:04:43 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_size(t_token *token)
{
	size_t	size;

	size = 0;
	while (token)
	{
		size++;
		token = token->next;
	}
	return (size);
}
