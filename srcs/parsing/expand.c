/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:07:56 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 11:57:32 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(t_data *data, char **line)
{
	t_check_quotes	check;
	size_t			i;

	if (!data || !line)
		return (0);
	i = 0;
	ft_memset(&check, 0, sizeof(t_check_quotes));
	if (ft_strchr(*line, '$') != NULL)
	{
		*line = extract_expand(*line, data->env);
		if (!*line)
			return (0);
	}
	return (1);
}
