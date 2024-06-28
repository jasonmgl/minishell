/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:48:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/05 18:41:07 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_envp *env, t_token *lst)
{
	t_sig	*sig;

	sig = get_sig();
	if (lst->next && lst->next->type == PARAM)
	{
		printf("env: `%s`: No such file or directory\n", lst->next->data);
		sig->status = 127;
	}
	else
	{
		while (env)
		{
			if (env->equal)
				printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
		sig->status = 0;
	}
}
