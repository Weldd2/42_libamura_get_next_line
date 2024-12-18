/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:27:04 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/19 00:43:56 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_get_next_line.h"

bool	found_endline(char *buffer, int *size)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (false);
	return (*size = i, true);
}

char	*gnl_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_r;
	int			size;

	size = 0;
	bytes_r = read(fd, buffer, BUFFER_SIZE);
	while (found_endline(buffer, &size) == false)
		bytes_r = read(fd, buffer, BUFFER_SIZE);
	line = mem_mgc_alloc(sizeof(char) * size);
	str_strlcpy(line, buffer, size);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	int fd = open("src/gnl_get_next_line.c", O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	printf("%s", gnl_get_next_line(fd));
	return (0);
}