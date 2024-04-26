/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:40:29 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 13:32:53 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_identification(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (ft_strncmp(lst->data, "export", 7) == 0 && lst->next)
		{
			lst = lst->next;
			while (lst && lst->type != PIPE && lst->type != STDIN
				&& lst->type != H_DOC && lst->type != STDOUT
				&& lst->type != A_STDOUT)
			{
				lst->type = VAR_ENV_EXP;
				lst = lst->next;
			}
		}
		else
			lst = lst->next;
	}
}

int	identify_builtins(t_token **bloc_lst)
{
	size_t	i;
	t_token	*ptr;

	if (!bloc_lst || !*bloc_lst)
		return (0);
	i = 0;
	while (bloc_lst[i])
	{
		ptr = bloc_lst[i];
		while (ptr)
		{
			if ((ft_strncmp(ptr->data, "echo", 5) == 0
					|| ft_strncmp(ptr->data, "cd", 3) == 0
					|| ft_strncmp(ptr->data, "pwd", 4) == 0
					|| ft_strncmp(ptr->data, "unset", 6) == 0
					|| ft_strncmp(ptr->data, "env", 4) == 0
					|| ft_strncmp(ptr->data, "exit", 5) == 0
					|| ft_strncmp(ptr->data, "export", 7) == 0) && !ptr->prev)
				ptr->type = BUILTIN;
			ptr = ptr->next;
		}
		i++;
	}
	return (1);
}

int	identify_var_env(t_token **bloc_lst, t_data *data)
{
	size_t	i;

	if (!bloc_lst || !*bloc_lst || !data)
		return (0);
	i = 0;
	data->nbr_cmd = 0;
	while (bloc_lst[i])
	{
		apply_identification(bloc_lst[i]);
		data->nbr_cmd += count_nbr_enum_lst(bloc_lst[i], CMD);
		data->nbr_cmd += count_nbr_enum_lst(bloc_lst[i++], BUILTIN);
	}
	return (1);
}
