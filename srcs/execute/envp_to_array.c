/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:18:56 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/13 16:11:12 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_lst_size(t_envp *env)
{
	t_envp	*tmp;
	size_t	n;

	n = 0;
	if (!env)
		return (n);
	tmp = env;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

static char	*free_strs(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*ft_strjoinf(char *s1, char *s2)
{
	size_t	ss1;
	size_t	ss2;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (free_strs(s1, s2));
	ss1 = ft_strlen(s1);
	ss2 = ft_strlen(s2);
	str = ft_calloc(ss1 + ss2 + 1, sizeof(char));
	if (str == NULL)
		return (free_strs(s1, s2));
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	free(s1 - ss1);
	free(s2 - ss2);
	return (str - ss1 - ss2);
}

static char	*join_name_and_value(t_envp *env)
{
	char	*str;

	str = ft_strjoinf(ft_strdup(env->name), ft_strdup("="));
	str = ft_strjoinf(str, ft_strdup(env->value));
	return (str);
}

char	**t_envp_to_array(t_envp *env)
{
	int		n;
	int		i;
	char	**envp;
	t_envp	*tmp;

	n = get_lst_size(env);
	envp = ft_calloc((n + 1), sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (i < n)
	{
		envp[i] = join_name_and_value(tmp);
		if (envp[i] == NULL)
		{
			while (i >= 0)
				free(envp[i--]);
			free(envp);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
