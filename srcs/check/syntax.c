/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:33:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 00:58:02 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	syn_err_chevron(enum e_redir type)
{
	if (type == STDIN)
		printf(S_ERR_CHEV_L);
	else if (type == H_DOC)
		printf(S_ERR_D_CHEV_L);
	else if (type == A_STDOUT)
		printf(S_ERR_D_CHEV_R);
	else if (type == STDOUT)
		printf(S_ERR_CHEV_R);
}

static void	handle_non_printable_character(t_data *data, char *str)
{
	error_handler("syntax error: non printable character\n");
	free(str);
	free_data(data);
	exit(2);
}

static void	update_in_quote(char c, bool *in_quote, char *quote)
{
	if (*in_quote == false && ((c == '\'' || c == '"')))
	{
		*in_quote = true;
		*quote = c;
	}
	else if (*in_quote == true && c == *quote)
	{
		*in_quote = false;
		*quote = '\0';
	}
}

int	check_operator(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp->next)
	{
		if ((tmp->type == PIPE && !tmp->next)
			|| (tmp->type == PIPE && !tmp->prev))
			return (printf(S_ERR_PIPE), ERR);
		else if ((tmp->type == STDIN || tmp->type == H_DOC
				|| tmp->type == A_STDOUT || tmp->type == STDOUT)
			&& (tmp->next->type == STDIN || tmp->next->type == H_DOC
				|| tmp->next->type == A_STDOUT || tmp->next->type == STDOUT))
			return (syn_err_chevron(tmp->next->type), ERR);
		else if ((((tmp->type == STDIN || tmp->type == H_DOC
						|| tmp->type == A_STDOUT || tmp->type == STDOUT)
					&& tmp->next->type == PIPE)
				|| (tmp->type == PIPE && tmp->next->type == PIPE)))
			return (printf(S_ERR_PIPE), ERR);
		tmp = tmp->next;
	}
	if (tmp->type == STDIN || tmp->type == H_DOC || tmp->type == A_STDOUT
		|| tmp->type == STDOUT || tmp->type == PIPE)
		return (printf(S_ERR_NW_LINE), ERR);
	return (SUCCESS);
}

int	check_syntax(t_data *data, char *str)
{
	size_t	i;
	bool	in_quote;
	char	quote;

	i = 0;
	in_quote = false;
	quote = '\0';
	while (str[i])
	{
		if (ft_isprint(str[i]) == 0 && ft_isspace(str[i]) == 0)
			handle_non_printable_character(data, str);
		update_in_quote(str[i], &in_quote, &quote);
		i++;
	}
	if (in_quote == true)
	{
		error_handler("syntax error: quotes not closed\n");
		return (ERR);
	}
	return (SUCCESS);
}
