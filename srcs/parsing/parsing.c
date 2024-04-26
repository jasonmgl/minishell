/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:44:13 by jmougel           #+#    #+#             */
/*   Updated: 2024/04/26 18:22:19 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	display_lst(t_token *lst)
{
	t_token	*ptr;

	if (!lst)
	{
		printf("Empty list\n");
		return ;
	}
	ptr = lst;
	while (ptr)
	{
		printf("%s\n", ptr->data);
		if (ptr->type == H_DOC)
			printf("H_DOC\n");
		else if (ptr->type == STDIN)
			printf("STDIN\n");
		else if (ptr->type == INFILE)
			printf("INFILE\n");
		else if (ptr->type == STDOUT)
			printf("STDOUT\n");
		else if (ptr->type == A_STDOUT)
			printf("A_STDOUT\n");
		else if (ptr->type == OUTFILE)
			printf("OUTFILE\n");
		else if (ptr->type == PIPE)
			printf("PIPE\n");
		else if (ptr->type == CMD)
			printf("CMD\n");
		else if (ptr->type == PARAM)
			printf("PARAM\n");
		else if (ptr->type == DELIMITER)
			printf("DELIMITER\n");
		else if (ptr->type == BUILTIN)
			printf("BUILTIN\n");
		else if (ptr->type == EXPORT)
			printf("EXPORT\n");
		else if (ptr->type == VAR_ENV_EXP)
			printf("VAR_ENV_EXP\n");
		else if (ptr->type == WORD)
			printf("WORD\n");
		ptr = ptr->next;
	}
	printf("\n");
}

static void	display_bloc(t_token **bloc_lst)
{
	int		i;

	if (!bloc_lst || !*bloc_lst)
	{
		printf("Empty bloc list\n");
		return ;
	}
	i = 0;
	while (bloc_lst[i])
	{
		printf("[BLOC %d]\n", i);
		display_lst(bloc_lst[i]);
		i++;
	}
}*/

int	edit_lst_type(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if ((lst->type == WORD || lst->type == PARAM) && !lst->prev)
			lst->type = CMD;
		else if (lst->type == WORD)
		{
			if (lst->prev->type == STDIN)
				lst->type = INFILE;
			else if (lst->prev->type == STDOUT || lst->prev->type == A_STDOUT)
				lst->type = OUTFILE;
			else if (lst->prev->type == OUTFILE || lst->prev->type == INFILE
				|| lst->prev->type == DELIMITER || lst->prev->type == PIPE)
				lst->type = CMD;
			else if (lst->prev->type == PARAM || lst->prev->type == CMD)
				lst->type = PARAM;
			else if (lst->prev->type == H_DOC)
				lst->type = DELIMITER;
		}
		lst = lst->next;
	}
	return (1);
}

int	parser(t_data *data, char *line, char *env[])
{
	t_token	*lst;

	if (!quotes_are_closed(line) || !check_syntax(line))
		return (0);
	if (!init_struct(data, env) || !expand(data, &line))
		return (0);
	//printf("%s\n", line);
	lst = tokeniser(line);
	//display_lst(lst);
	if (!lst)
		return (0);
	if (!edit_lst_type(lst) || !check_operator(lst))
		return (0);
	if (!lst_into_bloc(data, lst) || !remove_quotes(data->bloc_lst))
		return (0);
	if (!identify_builtins(data->bloc_lst))
		return (0);
	if (!identify_var_env(data->bloc_lst, data))
		return (0);
	ft_export(data, data->bloc_lst[0]);
	//display_bloc(data->bloc_lst);
	return (1);
}
