/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 14:50:44 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_name(char *arg, size_t *i)
{
	size_t	size;
	char	*name;

	size = get_first_match(arg, "=");
	name = ft_calloc(size + 1, sizeof(char));
	if (name == NULL)
		return (NULL);
	while (arg[*i] && (*i < size))
	{
		name[*i] = arg[*i];
		(*i)++;
	}
	name[*i] = '\0';
	return (name);
}

static char	*extract_value(char *arg, bool assigned)
{
	size_t	i;
	size_t	size;
	char	*value;

	if (assigned == false)
		return (ft_strdup(""));
	size = ft_strlen(arg);
	value = ft_calloc(size + 1, sizeof(char));
	if (value == NULL)
		return (NULL);
	i = 0;
	while (arg[i] && (i < size))
	{
		value[i] = arg[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

static int	venv_name_contain_punct(char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			error_handler("export: not valid in this context: ");
			error_handler(name);
			error_handler("\n");
			return (ERR);
		}
		i++;
	}
	return (SUCCESS);
}

int	add_venv_to_export(char *arg, t_envp **export)
{
	size_t	i;
	char	*name;
	char	*value;
	bool	assigned;
	t_envp	*venv;

	i = 0;
	assigned = value_is_assigned(arg);
	name = extract_name(arg, &i);
	if (name == NULL || str_is_equal(name, "") || venv_name_contain_punct(name))
	{
		free(name);
		return (ERR);
	}
	venv = get_venv(*export, name);
	value = extract_value(&arg[++i], assigned);
	if (value == NULL)
		return (ERR);
	if (venv == NULL)
		return (add_venv(export, name, value, assigned));
	else
		return (update_venv(*export, name, value));
}

int	add_venv_to_env(char *arg, t_envp **env)
{
	size_t	i;
	char	*name;
	char	*value;
	t_envp	*venv;

	i = 0;
	if (value_is_assigned(arg) == false)
		return (ERR);
	name = extract_name(arg, &i);
	if (name == NULL)
		return (ERR);
	venv = get_venv(*env, name);
	value = extract_value(&arg[++i], true);
	if (value == NULL)
		return (ERR);
	if (venv == NULL)
		return (add_venv(env, name, value, true));
	else
		return (update_venv(*env, name, value));
}
