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

static void	realloc_nodes(t_token *lst, t_token	**lst_bloc)
{
	bool	in_bloc;
	t_token	*tmp;
	int		i;

	i = 0;
	in_bloc = false;
	tmp = lst;
	while (tmp)
	{
		if (!in_bloc)
		{
			in_bloc = true;
			lst_bloc[i] = token_lstnew(tmp->data, tmp->type);
		}
		else if (tmp->type == PIPE)
		{
			in_bloc = false;
			i++;
		}
		else
			token_lstadd_back(&lst_bloc[i], token_lstnew(tmp->data, tmp->type));
		tmp = tmp->next;
	}
}

int	count_nbr_enum_lst(t_token *lst, enum e_redir type)
{
	int		nbr_enum;

	nbr_enum = 0;
	while (lst)
	{
		if (lst->type == type)
			nbr_enum++;
		lst = lst->next;
	}
	return (nbr_enum);
}

int	lst_into_bloc(t_data *data, t_token *lst)
{
	t_token	**lst_bloc;

	data->nbr_pipe = count_nbr_enum_lst(lst, PIPE);
	data->nbr_h_doc = count_nbr_enum_lst(lst, H_DOC);
	lst_bloc = ft_calloc((data->nbr_pipe + 1) + 1, sizeof(t_token *));
	if (!lst_bloc)
		return (ERR);
	realloc_nodes(lst, lst_bloc);
	lst_bloc[data->nbr_pipe + 1] = NULL;
	data->bloc_lst = lst_bloc;
	return (SUCCESS);
}
