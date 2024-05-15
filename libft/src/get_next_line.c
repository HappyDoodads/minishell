/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:06:44 by jdemers           #+#    #+#             */
/*   Updated: 2024/01/31 19:35:59 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*reset_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	nbytes;
	char	*line;

	line = ft_strdup(left_c);
	free(left_c);
	if (!line)
		return (NULL);
	if (ft_strchr(line, '\n'))
		return (line);
	while (line)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
			break ;
		if (nbytes == 0)
			return (line);
		buffer[nbytes] = '\0';
		left_c = ft_strjoin(line, buffer);
		free(line);
		line = left_c;
		if (ft_strchr(buffer, '\n'))
			return (line);
	}
	free(line);
	return (NULL);
}

static char	*set_line(char *line, char **line_addr)
{
	char	*leftovers;
	int		i;

	i = 0;
	if (line[0] == '\0')
		return (reset_buffer(line_addr));
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	leftovers = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!leftovers)
		return (reset_buffer(line_addr));
	if (*leftovers == '\0')
	{
		free(leftovers);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*left_c[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!left_c[fd])
		left_c[fd] = ft_strdup("");
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || !left_c[fd])
		return (reset_buffer(&left_c[fd]));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (reset_buffer(&left_c[fd]));
	line = fill_line_buffer(fd, left_c[fd], buffer);
	free(buffer);
	if (!line)
	{
		left_c[fd] = NULL;
		return (NULL);
	}
	left_c[fd] = set_line(line, &line);
	return (line);
}
