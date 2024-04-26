/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:33:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/25 13:38:09 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_are_closed(char *line)
{
	size_t			i;
	t_check_quotes	check;

	if (!line)
		return (0);
	i = 0;
	ft_memset(&check, 0, sizeof(t_check_quotes));
	while (line[i])
	{
		utils_check_quotes(line[i], &check);
		if (line[i] == '$' && check.in_s_quote)
			line[i] = line[i] * -1;
		i++;
	}
	if (check.s_quote % 2 != 0)
		return (printf(S_ERR_S_QUOTE), 0);
	else if (check.d_quote % 2 != 0)
		return (printf(S_ERR_D_QUOTE), 0);
	return (1);
}

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

int	check_operator(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		if ((lst->type == PIPE && !lst->next)
			|| (lst->type == PIPE && !lst->prev))
			return (printf(S_ERR_PIPE), 0);
		else if ((lst->type == STDIN || lst->type == H_DOC
				|| lst->type == A_STDOUT || lst->type == STDOUT)
			&& (lst->next->type == STDIN || lst->next->type == H_DOC
				|| lst->next->type == A_STDOUT || lst->next->type == STDOUT))
			return (syn_err_chevron(lst->next->type), 0);
		else if ((((lst->type == STDIN || lst->type == H_DOC
						|| lst->type == A_STDOUT || lst->type == STDOUT)
					&& lst->next->type == PIPE)
				|| (lst->type == PIPE && lst->next->type == PIPE)))
			return (printf(S_ERR_PIPE), 0);
		lst = lst->next;
	}
	if (lst->type == STDIN || lst->type == H_DOC || lst->type == A_STDOUT
		|| lst->type == STDOUT || lst->type == PIPE)
		return (printf(S_ERR_NW_LINE), 0);
	return (1);
}

int	check_syntax(char *line)
{
	t_check_quotes	check;
	size_t			i;

	if (!line)
		return (0);
	i = 0;
	ft_memset(&check, 0, sizeof(t_check_quotes));
	while (line[i])
	{
		if (line[i] == '\'')
			utils_check_quotes('\'', &check);
		else if (line[i] == '"')
			utils_check_quotes('"', &check);
		else if (line[i] == ';' && !check.in_d_quote && !check.in_s_quote)
			return (printf(S_ERR_S_COLON), 0);
		else if (line[i] == '\\' && !check.in_d_quote && !check.in_s_quote)
			return (printf(S_ERR_B_SLASH), 0);
		else if (line[i] == '&' && !check.in_d_quote && !check.in_s_quote)
			return (printf(S_ERR_ESPER), 0);
		i++;
	}
	return (1);
}
