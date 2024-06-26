/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:29:04 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/04 14:03:24 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	t_sig	*sig;
	char	*pwd;

	sig = get_sig();
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		sig->status = 1;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	sig->status = 0;
}
