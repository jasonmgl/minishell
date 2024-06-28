/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:14 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/30 17:39:31 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_lstadd_back(t_token **lst, t_token *new_node)
{
	t_token		*last;

	if (!new_node || !lst)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = token_lstlast(*lst);
	last->next = new_node;
	new_node->prev = last;
}

t_token	*token_lstnew(char *data, enum e_redir type)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->data = ft_strdup(data);
	new_node->type = type;
	return (new_node);
}

t_token	*token_lstlast(t_token *lst)
{
	t_token	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	token_remove_node(t_token **lst, t_token *node_to_del)
{
	t_token	*tmp;

	if (!lst || !*lst || !node_to_del)
		return ;
	tmp = *lst;
	while (tmp != node_to_del && tmp)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (!tmp->prev)
		*lst = tmp->next;
	else
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp->data);
	free(tmp);
}
