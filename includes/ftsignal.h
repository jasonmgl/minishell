/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsignal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:14:38 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/06 13:46:20 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSIGNAL_H
# define FTSIGNAL_H

# include "struct.h"

void	add_struct_to_sig(t_data *data, t_cmd **cmd);
t_sig	*get_sig(void);
void	init_sig(void);
void	signal_handler(int sign);
void	signal_child_handler(int sign);

#endif