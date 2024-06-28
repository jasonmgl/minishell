/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:49:15 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/13 15:56:09 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

int		add_venv(t_envp **env, char *name, char *value, bool assigned);
int		add_venv_to_env(char *arg, t_envp **env);
int		add_venv_to_export(char *arg, t_envp **export);
void	apply_identification(t_token *lst);
int		count_char(char *line, char c);
t_envp	*envp_lstlast(t_envp *lst);
void	error_handler(char *error);
int		find_quote(const char *line);
void	free_bloc_lst_token(t_token **token);
void	free_data(t_data *data);
void	free_lst_envp(t_envp *envp);
void	free_lst_token(t_token *token);
size_t	get_first_match(char *str, char *set);
size_t	get_token_size(t_token *token);
t_envp	*get_venv(t_envp *venv, char *name);
char	*get_venv_value(t_envp *env, char *name);
void	identify_builtins(t_data *data, t_token **bloc_lst);
int		init_env(t_data *data, char *envp[]);
bool	is_in_set(char *set, char c);
int		len_word_in_quotes(const char *line, int c);
size_t	max(size_t a, size_t b);
t_envp	*new_venv(char *name, char *value, bool equal);
int		str_is_equal(char *a, char *b);
void	token_lstadd_back(t_token **lst, t_token *new_node);
t_token	*token_lstlast(t_token *lst);
t_token	*token_lstnew(char *data, enum e_redir type);
void	token_remove_node(t_token **lst, t_token *node_to_del);
int		update_venv(t_envp *env, char *name, char *value);
bool	value_is_assigned(char *arg);
void	venv_addback(t_envp **env, t_envp *venv);

#endif