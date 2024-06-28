/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:44:35 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/13 15:08:14 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*get_venv(t_envp *venv, char *name)
{
	while (venv && venv->prev)
		venv = venv->prev;
	while (venv && str_is_equal(venv->name, name) == 0)
		venv = venv->next;
	if (venv == NULL)
		return (NULL);
	return (venv);
}

char	*get_venv_value(t_envp *env, char *name)
{
	t_envp	*venv;

	venv = get_venv(env, name);
	if (venv == NULL)
		return (ft_strdup(""));
	return (ft_strdup(venv->value));
}

int	update_venv(t_envp *env, char *name, char *value)
{
	t_envp	*venv;

	venv = get_venv(env, name);
	if (venv == NULL)
	{
		free(value);
		return (ERR);
	}
	free(name);
	free(venv->value);
	venv->equal = true;
	venv->value = value;
	return (SUCCESS);
}

int	add_venv(t_envp **env, char *name, char *value, bool assigned)
{
	t_envp	*venv;

	venv = get_venv(*env, name);
	if (venv == NULL)
	{
		venv = new_venv(name, value, assigned);
		if (venv == NULL)
			return (ERR);
		venv_addback(env, venv);
		return (SUCCESS);
	}
	if (update_venv(*env, name, value) == ERR)
		return (ERR);
	return (SUCCESS);
}

bool	value_is_assigned(char *arg)
{
	size_t	i;

	i = 0;
	while (arg && arg[i])
		if (arg[i++] == '=')
			return (true);
	return (false);
}
