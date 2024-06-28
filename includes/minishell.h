/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:36:55 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 16:03:59 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "builtins.h"
# include "execute.h"
# include "ftsignal.h"
# include "libft.h"
# include "parsing.h"
# include "utils.h"
# include "struct.h"

// Return values
# define ERR -1
# define SUCCESS 0

// Minishell Prompt
# define PROMPT			"\e[1m\e[3mminishell : \e[0m"

// Error messages
# define ERROR			"\e[1m\e[31merror\e[0m\n"
# define ERR_CD			"cd: too many arguments\n"
# define S_ERR_NO_PRINT	"syntax error no printable character detected\n"
# define S_ERR_S_QUOTE	"syntax error single quote not closed\n"
# define S_ERR_D_QUOTE	"syntax error double quotes not closed\n"
# define S_ERR_PIPE		"syntax error near unexpected token `|'\n"
# define S_ERR_NW_LINE	"syntax error near unexpected token `newline'\n"
# define S_ERR_CHEV_R	"syntax error near unexpected token `>'\n"
# define S_ERR_D_CHEV_R	"syntax error near unexpected token `>>'\n"
# define S_ERR_CHEV_L	"syntax error near unexpected token `<'\n"
# define S_ERR_D_CHEV_L	"syntax error near unexpected token `<<'\n"
# define S_ERR_S_COLON	"syntax error unexpected token `;'\n"
# define S_ERR_B_SLASH	"syntax error unexpected token `\\'\n"
# define S_ERR_ESPER	"syntax error unexpected token `&'\n"

#endif
