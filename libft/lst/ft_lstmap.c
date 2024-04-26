/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:40:39 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:25:05 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*lst_new;
	t_list		*lst_temp;
	void		*tmp_content;

	lst_new = NULL;
	if (!f || !lst)
		return (NULL);
	while (lst)
	{
		tmp_content = (*f)(lst->content);
		lst_temp = ft_lstnew(tmp_content);
		if (!lst_temp)
		{
			del(tmp_content);
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_new, lst_temp);
		lst = lst->next;
	}
	return (lst_new);
}
