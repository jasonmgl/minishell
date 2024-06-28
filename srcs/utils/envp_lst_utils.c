/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:14 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 16:39:22 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*new_venv(char *name, char *value, bool equal)
{
	t_envp	*venv;

	venv = ft_calloc(1, sizeof(t_envp));
	if (venv == NULL)
		return (NULL);
	venv->name = ft_strdup(name);
	venv->value = ft_strdup(value);
	if (equal)
		venv->equal = true;
	else
		venv->equal = false;
	free(name);
	free(value);
	return (venv);
}

void	venv_addback(t_envp **env, t_envp *venv)
{
	t_envp		*last;

	if (!*env)
	{
		*env = venv;
		return ;
	}
	last = envp_lstlast(*env);
	last->next = venv;
	venv->prev = last;
}

t_envp	*envp_lstlast(t_envp *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
