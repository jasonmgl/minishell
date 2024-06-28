/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:48:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 18:56:45 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_venv(t_envp *node)
{
	t_envp	*next;

	if (node->next == NULL)
		return ;
	next = node->next;
	next->prev = node->prev;
	if (node->prev)
		node->prev->next = next;
	node->prev = next;
	node->next = next->next;
	if (next->next)
		next->next->prev = node;
	next->next = node;
}

static void	sort_env(t_envp *env)
{
	size_t	i;

	while (env && env->next)
	{
		i = 0;
		while (env->name[i] && env->next->name[i] && \
		env->name[i] == env->next->name[i])
			i++;
		if (env->name[i] > env->next->name[i])
		{
			swap_venv(env);
			while (env->prev)
				env = env->prev;
		}
		else
			env = env->next;
	}
}

static void	print_export(t_envp *env)
{
	t_envp	*tmp;

	sort_env(env);
	while (env && env->prev)
		env = env->prev;
	tmp = env;
	while (tmp)
	{
		if (tmp->equal)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}

void	export(t_data *data, t_token *token)
{
	size_t	nb_args;
	t_sig	*sig;

	sig = get_sig();
	nb_args = get_token_size(token);
	if (nb_args == 1)
	{
		print_export(data->export);
		sig->status = 0;
		return ;
	}
	while (token)
	{
		if (token->type == VAR_ENV_EXP)
		{
			if (add_venv_to_export(token->data, &data->export) == SUCCESS)
				add_venv_to_env(token->data, &data->env);
		}
		token = token->next;
	}
}
