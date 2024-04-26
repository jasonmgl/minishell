/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:44:21 by rsequeir          #+#    #+#             */
/*   Updated: 2024/04/25 13:46:12 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_command_path(char *command, char **envp)
{
	char	*command_path;
	char	**path;

	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		else if (access(command, F_OK) == 0 && access(command, X_OK) == -1)
			print_permission_denied(command);
		else
			print_command_not_found(command);
		return (NULL);
	}
	path = get_env_path(envp);
	command_path = search_in_path(command, path);
	if (command_path == NULL)
		print_command_not_found(command);
	free_split(path);
	return (command_path);
}

// A MODIFIER
/* char	**get_arg(char	*argv)
{
	char	**arg;

	arg = ft_split(argv, ' ');
	if (arg == NULL)
	{
		print_strerror();
		exit(ERROR);
	}
	return (arg);
} */
