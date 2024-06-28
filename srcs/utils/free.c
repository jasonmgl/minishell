/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:41:15 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 15:58:37 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_lst_envp(t_envp *envp)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	while (envp->prev)
		envp = envp->prev;
	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_bloc_lst_token(t_token **token)
{
	size_t	i;

	if (!token || !*token)
		return ;
	i = 0;
	while (token[i])
		free_lst_token(token[i++]);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
		free_lst_envp(data->env);
	if (data->export)
		free_lst_envp(data->export);
	if (data->bloc_lst)
	{
		free_bloc_lst_token(data->bloc_lst);
		if (data->bloc_lst)
		{
			free(data->bloc_lst);
			data->bloc_lst = NULL;
		}
	}
	if (data->lst)
		free_lst_token(data->lst);
	restore_std_fd(data);
	ft_memset(data, 0, sizeof(t_data));
}
