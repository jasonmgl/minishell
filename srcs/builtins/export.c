/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:48:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 17:53:14 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(t_envp *export)
{
	t_envp	*next_node;

	if (!export->next)
		return ;
	next_node = export->next;
	next_node->prev = export->prev;
	if (export->prev)
		export->prev->next = next_node;
	export->prev = next_node;
	export->next = next_node->next;
	if (next_node->next)
		next_node->next->prev = export;
	next_node->next = export;
}

static int	sort(t_envp	*tmp)
{
	size_t	i;

	i = 0;
	while (tmp->next)
	{
		if (tmp->name[i] > tmp->next->name[i])
		{
			swap(tmp);
			while (tmp->prev)
				tmp = tmp->prev;
			i = 0;
		}
		else if (tmp->name[i] == tmp->next->name[i])
			i++;
		else
		{
			tmp = tmp->next;
			i = 0;
		}
	}
	return (1);
}

static int	display_env_var(t_envp *export)
{
	if (!export)
		return (0);
	sort(export);
	while (export->prev)
		export = export->prev;
	while (export)
	{
		printf("declare -x %s=%s\n", export->name, export->value);
		export = export->next;
	}
	return (1);
}

int	ft_export(t_data *data, t_token *lst)
{
	if (!data || !lst)
		return (0);
	if (ft_strncmp(lst->data, "export", 7) == 0 && lst->next)
	{
		while (lst)
		{
			if (lst->type == VAR_ENV_EXP)
			{
				if (!extract_var_env(lst->data, &data->export))
					return (0);
				if (!extract_var_env(lst->data, &data->env))
					return (0);
			}
			lst = lst->next;
		}
	}
	else if (ft_strncmp(lst->data, "export", 7) == 0)
	{
		if (!display_env_var(data->export))
			return (0);
	}
	return (1);
}
