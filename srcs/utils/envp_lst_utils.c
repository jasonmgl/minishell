/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:14 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 13:19:00 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*envp_lstnew(char *name, char *value)
{
	t_envp	*new_node;

	new_node = ft_calloc(1, sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	return (new_node);
}

void	envp_lstadd_back(t_envp **lst, t_envp *new_node)
{
	t_envp		*last;

	if (!new_node || !lst)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = envp_lstlast(*lst);
	last->next = new_node;
	new_node->prev = last;
}

t_envp	*envp_lstlast(t_envp *lst)
{
	t_envp	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
