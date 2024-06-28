/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:24:42 by rsequeir          #+#    #+#             */
/*   Updated: 2024/05/05 23:18:41 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_alnum(int fd)
{
	char	c;

	c = 0;
	while (!ft_isalnum(c))
	{
		if (!read(fd, &c, 1))
			return (0);
		c = (char)(((unsigned char) c) % 126);
	}
	return (c);
}

char	*create_tmp_file(void)
{
	int		fd;
	int		i;
	char	*file;
	char	c;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	file = ft_strdup("/goinfre/");
	i = 9;
	while (i < 20)
	{
		c = get_alnum(fd);
		file = ft_strjoin_free(file, &c);
		i++;
	}
	close(fd);
	return (file);
}

void	delete_tmp_files(t_data *data, t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while (i < data->nbr_cmd)
	{
		if (cmd[i]->here_doc)
			unlink(cmd[i]->infile);
		i++;
	}
}
