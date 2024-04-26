/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:09:31 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 18:20:57 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var_env(char *name, t_envp *env)
{
	t_envp	*ptr;
	char	*value;

	value = ft_strdup("");
	if (!name || !env)
		return (value);
	ptr = env;
	while (ptr)
	{
		if (ft_strncmp(name, ptr->name, ft_strlen(name) + 1) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (value);
}

static char	*get_new_str(char **ar)
{
	size_t	i;
	char	*new_str;

	if (!ar)
		return (NULL);
	i = 0;
	new_str = NULL;
	while (ar[i])
	{
		new_str = ft_strjoin_free(new_str, ar[i]);
		if (!new_str)
			return (NULL);
		i++;
	}
	return (new_str);
}

static int	expand_var(char **line, t_envp *env)
{
	char	*tmp;
	t_sig	*sig;

	tmp = NULL;
	sig = get_sig();
	if (ft_strchr(*line, '$'))
	{
		if (ft_strncmp(&(*line)[1], "?", 1) == 0)
		{
			free(*line);
			*line = ft_itoa(sig->status);
			if (!*line)
				return (0);
		}
		else
		{
			tmp = find_var_env(&(*line)[1], env);
			free(*line);
			*line = ft_strdup(tmp);
			if (!*line)
				return (0);
		}
	}
	return (1);
}

static char	*replace_var_env(char *str, t_envp *env)
{
	char	**ar;
	char	*new_str;
	size_t	i;

	if (!str || !env)
		return (NULL);
	i = 0;
	ar = ft_split_set(str, "'\"$ ");
	if (!ar)
		return (NULL);
	while (ar[i])
		expand_var(&ar[i++], env);
	new_str = get_new_str(ar);
	free_split(ar);
	return (new_str);
}

char	*extract_expand(char *str, t_envp *env)
{
	char	*dollar;
	char	*new_str;

	//printf("str in expand : %s\n", str);
	if (!str || !env)
		return (NULL);
	dollar = ft_strchr(str, '$');
	if (dollar == NULL)
		return (str);
	new_str = replace_var_env(str, env);
	if (!new_str)
		return (NULL);
	free(str);
	return (extract_expand(new_str, env));
}
