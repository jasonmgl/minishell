/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 18:21:16 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_name(char *envp)
{
	int		i;
	int		len_word;
	char	*name;

	if (!envp)
		return (NULL);
	i = 0;
	len_word = len_word_with_set(envp, "=");
	name = ft_calloc(len_word + 1, sizeof(char));
	if (!name)
		return (NULL);
	while (i < len_word && envp[i])
	{
		name[i] = envp[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char	*extract_value(char *envp)
{
	int		i;
	int		len_word;
	char	*value;

	//printf("envp after = : %s\n", envp);
	if (!envp)
		return (NULL);
	i = 0;
	len_word = ft_strlen(&envp[i]);
	value = ft_calloc(len_word + 1, sizeof(char));
	if (!value)
		return (NULL);
	while (i < len_word && envp[i])
	{
		value[i] = envp[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

static int	extract(t_envp *tmp, char *name, char *value)
{
	if (!tmp || !name)
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	extract_var_env(char *envp, t_envp **envp_lst)
{
	size_t	i;
	char	*name;
	char	*value;
	t_envp	*tmp;

	if (!envp)
		return (0);
	i = 0;
	name = extract_name(envp);
	//printf("name: %s\n", name);
	//printf("envp: %s\n", envp);
	while (envp[i] && envp[i] != '=')
		i++;
	if (envp[i] == '=')
		value = extract_value(&envp[++i]);
	else
		value = ft_strdup("");
	tmp = *envp_lst;
	if (!extract(tmp, name, value) && name)
	{
		tmp = envp_lstnew(name, value);
		if (!tmp)
			return (0);
		envp_lstadd_back(envp_lst, tmp);
	}
	return (1);
}
