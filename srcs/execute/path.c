/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:41:57 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/05 23:18:09 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_slashes(char **path)
{
	char	*new_path;
	int		i;

	i = 0;
	while (path[i])
	{
		new_path = ft_strjoin(path[i], "/");
		if (new_path == NULL)
			return (ERR);
		free(path[i]);
		path[i++] = new_path;
	}
	return (SUCCESS);
}

static char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

char	**get_env_path(char **envp)
{
	char	*path_env;
	char	**path_dirs;

	path_env = find_path_env(envp);
	if (path_env == NULL)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (path_dirs == NULL)
		return (NULL);
	if (append_slashes(path_dirs) == ERR)
	{
		free_split(path_dirs);
		return (NULL);
	}
	return (path_dirs);
}
