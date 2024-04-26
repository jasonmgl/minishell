/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsequeir <rsequeir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:52:18 by rsequeir          #+#    #+#             */
/*   Updated: 2024/04/16 19:26:07 by rsequeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	has_new_line(char *cache)
{
	while (cache && *cache && *cache != '\n')
		cache++;
	if (*cache == '\0')
		return (0);
	return (1);
}

char	*get_line(char *cache, char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < BUFFER_SIZE && cache[i] && cache[i] != '\n')
		i++;
	tmp = ft_substr(cache, 0, i + 1);
	line = ft_strjoin_free(line, tmp);
	free(tmp);
	return (line);
}

void	update_cache(char *cache)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < BUFFER_SIZE && cache[i] && cache[i] != '\n')
		i++;
	i++;
	j = 0;
	while (i < BUFFER_SIZE + 1)
		cache[j++] = cache[i++];
}

int	ft_read_file(int fd, char *cache, char **line)
{
	int		read_bytes;
	size_t	i;

	while (!has_new_line(cache))
	{
		*line = ft_strjoin_free(*line, cache);
		i = 0;
		while (i < BUFFER_SIZE)
			cache[i++] = '\0';
		read_bytes = read(fd, cache, BUFFER_SIZE);
		if (read_bytes == -1)
			return (0);
		cache[read_bytes] = '\0';
		if (!cache[0])
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	cache[BUFFER_SIZE + 1];
	char		*line;
	int			has_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	has_read = ft_read_file(fd, cache, &line);
	if (!has_read && !*line)
	{
		free(line);
		return (NULL);
	}
	line = get_line(cache, line);
	update_cache(cache);
	return (line);
}
