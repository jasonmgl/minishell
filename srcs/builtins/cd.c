/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:29:04 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 12:28:57 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_envp *env, t_token *token, size_t nb_args)
{
	if (nb_args == 1 || str_is_equal(token->data, "~"))
		return (get_venv_value(env, "HOME"));
	else if (str_is_equal(token->data, "-"))
		return (get_venv_value(env, "OLDPWD"));
	else if (is_absolute_path(token->data))
		return (ft_strdup(token->data));
	else
		return (get_relative_path(env, token->data));
}

int	do_chdir(char *path, char *arg, t_sig *sig)
{
	char	*print;

	if (chdir(path) == ERR)
	{
		if (is_absolute_path(arg))
			print = path;
		else
			print = arg;
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(print, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		sig->status = 1;
		return (ERR);
	}
	return (SUCCESS);
}

void	update_venvs(t_envp *env, t_envp *export, char *path)
{
	char	*env_pwd;
	char	*export_pwd;

	env_pwd = get_venv_value(env, "PWD");
	export_pwd = get_venv_value(export, "PWD");
	update_venv(env, ft_strdup("OLDPWD"), env_pwd);
	update_venv(export, ft_strdup("OLDPWD"), export_pwd);
	update_venv(env, ft_strdup("PWD"), ft_strdup(path));
	update_venv(export, ft_strdup("PWD"), ft_strdup(path));
}

int	cd(t_envp *env, t_envp *export, t_token *token)
{
	size_t	nb_args;
	char	*path;
	char	*arg;
	t_sig	*sig;

	sig = get_sig();
	nb_args = get_token_size(token);
	if (check_args(nb_args, sig) == ERR)
		return (1);
	if (nb_args > 1)
		arg = token->next->data;
	else
		arg = NULL;
	path = get_path(env, token->next, nb_args);
	if (str_is_equal(path, ""))
	{
		printf("cd: HOME not set\n");
		sig->status = 1;
		return (free(path), 1);
	}
	if (do_chdir(path, arg, sig) == ERR)
		return (free(path), 1);
	update_venvs(env, export, path);
	sig->status = 0;
	return (free(path), 0);
}
