/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:41:15 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 15:52:16 by jmougel          ###   ########.fr       */
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
		free(tmp);
	}
}

void	free_lst_envp(t_envp *envp)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_bloc_lst_token(t_token **token)
{
	size_t	i;

	if (!token || !*token)
		return ;
	i = 0;
	while (token[i])
	{
		free_lst_token(token[i]);
		free(token[i]);
		i++;
	}
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
		free_bloc_lst_token(data->bloc_lst);
	ft_memset(data, 0, sizeof(t_data));
}
