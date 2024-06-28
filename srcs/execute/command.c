/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:44:21 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 00:53:50 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_absolute_path(char *command, int *status)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	else if (access(command, F_OK) == 0 && access(command, X_OK) == -1)
	{
		*status = 126;
		print_permission_denied(command);
	}
	else
	{
		*status = 127;
		print_command_not_found(command);
	}
	return (NULL);
}

static char	*get_rel_path(char *command, char **envp, int *status)
{
	char	*command_path;
	char	**path;

	path = get_env_path(envp);
	command_path = search_in_path(command, path);
	if (command_path == NULL)
	{
		*status = 127;
		print_command_not_found(command);
	}
	free_split(path);
	return (command_path);
}

char	*search_in_path(char *command, char **path)
{
	char	*full_path;
	int		i;

	full_path = NULL;
	i = 0;
	while (path && path[i])
	{
		full_path = ft_strjoin(path[i++], command);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
	}
	return (NULL);
}

char	*get_command_path(char *command, char **envp, int *status)
{
	if (ft_strchr(command, '/') != NULL)
		return (get_absolute_path(command, status));
	return (get_rel_path(command, envp, status));
}
