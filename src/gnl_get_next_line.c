/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:27:04 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/08 15:44:06 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*gnl_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	char		*line;

	line = mem_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (1)
	{
		str_strcat_realloc(&line, buffer, BUFFER_SIZE);
		if (str_strcontains(buffer, '\n') != -1)
			break ;
		if (fd == -1 || read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			if (line[0] == '\0')
				return (free(line), NULL);
			buffer[0] = '\0';
			return (line);
		}
	}
	str_replace_sub(&line, 0, str_strcontains(line, '\n') + 1);
	str_slice(buffer, str_strcontains(buffer, '\n') + 1, BUFFER_SIZE + 1);
	return (line);
}
