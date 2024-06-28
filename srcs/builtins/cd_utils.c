/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:28:14 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 14:56:51 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(size_t nb_args, t_sig *sig)
{
	if (nb_args > 2)
	{
		error_handler("cd: too many arguments\n");
		sig->status = 1;
		return (ERR);
	}
	return (SUCCESS);
}

int	is_absolute_path(char *arg)
{
	if (arg && ((arg[0] == '/') || (arg[0] == '~')))
		return (1);
	return (0);
}

char	*get_relative_path(t_envp *env, char *arg)
{
	char	*pwd;
	char	*path;

	pwd = get_venv_value(env, "PWD");
	path = ft_strjoin(pwd, "/");
	free(pwd);
	path = ft_strjoin_free(path, arg);
	return (path);
}
