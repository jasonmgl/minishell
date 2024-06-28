/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:07:56 by jmougel           #+#    #+#             */
/*   Updated: 2024/05/06 16:27:16 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_str(t_envp *env, char *str, size_t *i)
{
	char	*name;
	char	*value;
	char	*new_str;
	size_t	j;

	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	name = ft_substr(str, *i + 1, j - *i - 1);
	name = remove_quotes(name);
	if (name == NULL)
		return (NULL);
	value = get_venv_value(env, name);
	free(name);
	if (value == NULL)
		return (NULL);
	crypt_value(&value);
	new_str = ft_strjoin_free(ft_substr(str, 0, *i), value);
	if (new_str == NULL)
		return (free(value), NULL);
	*i = ft_strlen(new_str);
	new_str = ft_strjoin_free(new_str, &str[j]);
	if (new_str == NULL)
		return (free(value), free(str), NULL);
	return (free(value), free(str), new_str);
}

static char	*expand_status(t_sig *sig, char *str, size_t *i)
{
	char	*value;
	char	*new_str;
	char	*tmp;
	size_t	j;

	j = *i + 2;
	value = ft_itoa(sig->status);
	if (value == NULL)
		return (NULL);
	new_str = ft_strjoin_free(ft_substr(str, 0, *i), value);
	free(value);
	if (new_str == NULL)
		return (NULL);
	*i = ft_strlen(new_str);
	tmp = ft_strdup(&str[j]);
	new_str = ft_strjoin_free(new_str, tmp);
	free(tmp);
	if (new_str == NULL)
		return (NULL);
	free(str);
	return (new_str);
}

void	decrypt_value(char **value)
{
	size_t	i;

	i = 0;
	while ((*value)[i])
	{
		if ((*value)[i] == '"' * -1)
			(*value)[i] *= -1;
		i++;
	}
}

void	crypt_value(char **value)
{
	size_t	i;

	i = 0;
	while ((*value)[i])
	{
		if ((*value)[i] == '"')
			(*value)[i] *= -1;
		i++;
	}
}

int	expand(t_data *data, char **str, bool heredoc)
{
	size_t	i;
	bool	in_quote;
	t_sig	*sig;

	i = 0;
	in_quote = false;
	sig = get_sig();
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && heredoc == false)
		{
			if ((i > 0 && (*str)[i - 1] != '"') || i == 0)
				in_quote = !in_quote;
		}
		if ((*str)[i] == '$' && (*str)[i + 1] == '?' && !in_quote)
			*str = expand_status(sig, *str, &i);
		else if ((*str)[i] == '$' && !in_quote)
			*str = expand_str(data->env, *str, &i);
		else
			i++;
		if (*str == NULL)
			return (ERR);
	}
	return (SUCCESS);
}
