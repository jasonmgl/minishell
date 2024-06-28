/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:26:05 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 16:27:54 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

// Struct
typedef struct s_envp
{
	bool			equal;
	char			*name;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;
//
typedef enum e_redir
{
	H_DOC,
	STDIN,
	INFILE,
	STDOUT,
	A_STDOUT,
	OUTFILE,
	PIPE,
	CMD,
	PARAM,
	DELIMITER,
	BUILTIN,
	EXPORT,
	VAR_ENV_EXP,
	WORD
}	t_redir;
//
typedef struct s_token
{
	bool			in_s_quote;
	char			*data;
	enum e_redir	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;
//
typedef struct s_data
{
	size_t		nbr_h_doc;
	size_t		nbr_cmd;
	size_t		nbr_pipe;
	char		**envp;
	t_envp		*env;
	t_envp		*export;
	t_token		**bloc_lst;
	t_token		*lst;
	int			fd_stdin;
	int			fd_stdout;
}	t_data;
//
typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		pfd[2];
	int		here_doc;
	int		append;
	int		builtin;
	int		i;
	bool	last;
	char	*infile;
	char	*outfile;
	char	**delimiters;
	char	**outs;
	char	**command;
	char	**env;
}			t_cmd;
//
typedef struct s_sig
{
	int		status;
	int		child;
	int		sigint;
	int		i;
	int		heredoc_fd;
	char	*heredoc_infile;
	t_data	*data;
	t_cmd	**cmd;
}		t_sig;
//
typedef struct s_quotes
{
	size_t	i;
	size_t	j;
	bool	in_quote;
	char	quote;
}	t_quotes;
//

#endif
