/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:36:55 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 18:09:46 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/**
 * @file minishell.h
 * @author jmougel
 * @date 2024/04/11
 * @brief Header file for the minishell program.
 */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"

// Prompt
# define PROMPT			"\e[1m\e[3mminishell : \e[0m"

//
# define ERR -1
# define SUCCESS 0

// Error messages
# define ERROR			"\e[1m\e[31merror\e[0m\n"
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
/**/

/**
 * @brief Enumeration of redirection types.
 */
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

/**
 * @brief Structure for checking quotes.
 */
typedef struct s_check_quotes
{
	size_t	s_quote;
	size_t	d_quote;
	bool	in_s_quote;
	bool	in_d_quote;
}	t_check_quotes;

/**
 * @brief Structure for a token.
 */
typedef struct s_token
{
	char			*data;
	enum e_redir	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/**
 * @brief Structure for an environment variable.
 */
typedef struct s_envp
{
	char			*name;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

/**
 * @brief Structure for the data of the minishell program.
 */
typedef struct s_data
{
	size_t		nbr_h_doc;
	size_t		nbr_cmd;
	size_t		nbr_pipe;
	char		**envp;
	t_envp		*env;
	t_envp		*export;
	t_token		**bloc_lst;
}	t_data;

typedef struct s_cmd
{
	int		fd_infile;
	int		fd_outfile;
	int		pipe_fd[2];
	int		here_doc;
	int		append;
	int		builtin;
	char	*delimiter;
	char	*infile;
	char	*outfile;
	char	**command;
	char	**env;
}			t_cmd;

typedef struct s_sig
{
	int	sig;
	int	work;
	int	status;
	int	listen;
	int	child;
	int	heredoc;
}		t_sig;

// Function prototypes
int		quotes_are_closed(char *line);
int		check_operator(t_token *lst);
int		check_syntax(char *line);
//
void	token_remove_node(t_token **lst, t_token *node_to_del);
void	token_lstadd_back(t_token **lst, t_token *new_node);
t_token	*token_lstnew(char *data, enum e_redir type);
t_token	*token_lstlast(t_token *lst);
//
void	envp_lstadd_back(t_envp **lst, t_envp *new_node);
t_envp	*envp_lstnew(char *name, char *value);
t_envp	*envp_lstlast(t_envp *lst);
//
void	utils_check_quotes(char c, t_check_quotes *check);
int		find_quote(const char *line);
int		len_word_with_set(const char *line, const char *set_char);
int		len_word_in_quotes(const char *line, int c);
//
void	free_lst_envp(t_envp *envp);
void	free_lst_token(t_token *token);
void	free_bloc_lst_token(t_token **token);
void	free_data(t_data *data);
//
int		remove_quotes(t_token **blocs);
int		lst_into_bloc(t_data *data, t_token *lst);
int		count_nbr_enum_lst(t_token *lst, enum e_redir type);
int		expand(t_data *data, char **line);
//
int		parser(t_data *data, char *line, char *env[]);
int		edit_lst_type(t_token *lst);
//
char	*extract_expand(char *str, t_envp *env);
t_token	*tokeniser(char *line);
char	**ft_split_set(char *s, char *set);
//
int		init_struct(t_data *data, char **env);
//
t_sig	*get_sig(void);
void	init_sig(void);
//
int		ft_pwd(void);
int		ft_env(t_data *data);
int		ft_export(t_data *data, t_token *lst);
//
int		identify_builtins(t_token **bloc_lst);
int		identify_var_env(t_token **bloc_lst, t_data *data);
//
int		extract_var_env(char *envp, t_envp **envp_lst);
//
void	do_pipe(int pipe_fd[2]);
void	close_fds(int pipe_fd[2]);
pid_t	do_fork(int pipe_fd[2]);
char	*create_tmp_file(void);
int		read_lines(t_cmd **cmd);

void	check_access(char *file);
int		open_infile(char *file, int pipe_fd[2]);
int		open_outfile(char *file, int pipe_fd[2], int append);
//
char	*search_in_path(char *command, char **path);
char	*get_command_path(char *command, char **envp);
//
void	print_strerror(void);
void	print_file_error(char *file);
void	print_command_not_found(char *command);
void	print_permission_denied(char *file);
//
void	free_split(char **split);
char	**get_env_path(char **envp);
//
int		max(int a, int b);
int		execute_all(t_data data);

#endif