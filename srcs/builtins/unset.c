/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:34:27 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 18:49:59 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete(t_envp **envp)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	tmp = *envp;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp->name);
	tmp->name = NULL;
	free(tmp->value);
	tmp->value = NULL;
	free(tmp);
	tmp = NULL;
}

static void	find_and_delete(t_envp **envp, t_token *tmp)
{
	t_envp	*head;

	while ((*envp)->prev)
		*envp = (*envp)->prev;
	head = *envp;
	while (envp && *envp)
	{
		if (str_is_equal((*envp)->name, tmp->data))
		{
			if (str_is_equal(head->name, (*envp)->name))
			{
				if ((*envp)->next)
					head = (*envp)->next;
				else
					head = NULL;
			}
			delete(envp);
			*envp = head;
			return ;
		}
		*envp = (*envp)->next;
	}
	*envp = head;
}

void	unset(t_data *data, t_token *lst)
{
	t_token	*tmp;

	tmp = lst->next;
	if (str_is_equal(lst->data, "unset") && tmp)
	{
		while (tmp && tmp->type == PARAM)
		{
			find_and_delete(&data->env, tmp);
			find_and_delete(&data->export, tmp);
			tmp = tmp->next;
		}
	}
}
