/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:27:04 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/19 04:50:54 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

bool	found_endline(char *line, int *pos)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (false);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (false);
	return (*pos = i, true);
}

char	*gnl_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			pos;
	int			bytes_read;
	size_t		line_size;

	line_size = BUFFER_SIZE;
	line = mem_mgc_calloc(BUFFER_SIZE, sizeof(char));
	str_strlcat(line, buffer, BUFFER_SIZE);
	while (found_endline(line, &pos) == false)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (line);
		line_size += BUFFER_SIZE;
		line = mem_realloc(line, line_size - BUFFER_SIZE, line_size);
		str_strlcat(line, buffer, line_size);
	}
	str_strlcpy(buffer, str_substr(line, pos + 1, str_strlen(line) - pos), \
		BUFFER_SIZE);
	line = str_substr(line, 0, pos + 1);
	return (line);
}
