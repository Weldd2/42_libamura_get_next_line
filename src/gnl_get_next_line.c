/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:27:04 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 15:45:12 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static int	read_to_buffer(int fd, char *buffer)
{
	ssize_t	bytes_read;

	if (str_strlen(buffer) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		return ((int)bytes_read);
	}
	return (1);
}

static char	*extend_line_with_buffer(char *line, char *buffer, size_t *index)
{
	line = mem_realloc(line, ((*index) + 1) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	if ((*index) == 0)
		line[0] = '\0';
	str_strlcat(line, buffer, (BUFFER_SIZE + 1) * ((*index) + 1));
	buffer[0] = '\0';
	(*index)++;
	return (line);
}

static int	check_and_slice_line(char *line, char *buffer)
{
	int	backline_pos;

	backline_pos = str_strcontains(line, '\n');
	if (backline_pos != -1)
	{
		str_strlcpy(buffer, line + backline_pos + 1, \
			str_strlen(line) - backline_pos);
		str_slice(line, 0, backline_pos + 1);
	}
	return (backline_pos);
}

char	*gnl_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	char		*line;
	size_t		i;
	int			backline_pos;
	int			bytes_read;

	i = 0;
	line = NULL;
	while (1)
	{
		bytes_read = read_to_buffer(fd, buffer);
		if (bytes_read <= 0)
		{
			if (str_strlen(line) != 0)
				return (line);
			return (mem_free(line), NULL);
		}
		line = extend_line_with_buffer(line, buffer, &i);
		if (!line)
			return (NULL);
		backline_pos = check_and_slice_line(line, buffer);
		if (backline_pos != -1)
			return (line);
	}
}
