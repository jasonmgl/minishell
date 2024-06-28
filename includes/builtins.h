/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:30:38 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 16:22:13 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

int		cd(t_envp *env, t_envp *export, t_token *token);
void	echo(char **args);
void	env(t_envp *env, t_token *lst);
void	export(t_data *data, t_token *token);
void	ft_exit(t_data *data, t_cmd **cmd, t_cmd **head);
void	pwd(void);
void	unset(t_data *data, t_token *lst);

int		check_args(size_t nb_args, t_sig *sig);
char	*get_relative_path(t_envp *env, char *arg);
int		is_absolute_path(char *arg);

#endif