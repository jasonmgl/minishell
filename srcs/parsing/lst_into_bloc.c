/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_into_bloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:24:36 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/03 17:50:01 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nbr_enum_lst(t_token *lst, enum e_redir type)
{
	int		nbr_enum;

	if (!lst)
		return (0);
	nbr_enum = 0;
	while (lst)
	{
		if (lst->type == type)
			nbr_enum++;
		lst = lst->next;
	}
	return (nbr_enum);
}

static void	delete(t_token **lst, bool *in_bloc)
{
	t_token	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	if (tmp->prev)
		tmp->prev->next = NULL;
	if (tmp->next)
		tmp->next->prev = NULL;
	*lst = (*lst)->next;
	free(tmp->data);
	free(tmp);
	*in_bloc = false;
}

static void	delete_pipe_node(t_token *lst, t_token	**lst_bloc)
{
	bool	in_bloc;
	int		i;

	i = 0;
	in_bloc = false;
	while (lst)
	{
		if (!in_bloc)
		{
			lst_bloc[i++] = lst;
			in_bloc = true;
		}
		if (lst->type == PIPE)
			delete(&lst, &in_bloc);
		else
			lst = lst->next;
	}
}

int	lst_into_bloc(t_data *data, t_token *lst)
{
	t_token	**lst_bloc;

	data->nbr_pipe = count_nbr_enum_lst(lst, PIPE);
	data->nbr_h_doc = count_nbr_enum_lst(lst, H_DOC);
	lst_bloc = ft_calloc((data->nbr_pipe + 1) + 1, sizeof(t_token *));
	if (!lst_bloc)
		return (0);
	delete_pipe_node(lst, lst_bloc);
	data->bloc_lst = lst_bloc;
	return (1);
}
