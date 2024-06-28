/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:32:48 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 00:09:18 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

int		check_operator(t_token *lst);
int		check_syntax(t_data *data, char *str);
int		count_nbr_enum_lst(t_token *lst, enum e_redir type);
void	crypt_value(char **value);
void	decrypt_value(char **value);
void	edit_lst_type(t_token *lst);
int		expand(t_data *data, char **line, bool heredoc);
int		lst_into_bloc(t_data *data, t_token *lst);
int		parser(t_data *data, char *line);
char	*remove_quotes(char *line);
t_token	*tokeniser(char *line);

#endif