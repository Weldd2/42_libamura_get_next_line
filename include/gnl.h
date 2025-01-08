/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:28:48 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/08 15:43:54 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "str.h"

/**
 * Reads the next line from the file descriptor `fd`, including the newline 
 * character if present, and returns it as a dynamically allocated string.
 *
 * This function maintains an internal static buffer to store data read from 
 * `fd`. It continuously appends content from this buffer to the line being 
 * constructed until a newline character is encountered or the end of file/input
 * is reached. The function handles buffer management by preserving leftover 
 * characters for future calls.
 *
 * The process is as follows:
 * - Allocates an initial buffer `line` to accumulate the characters.
 * - Repeatedly concatenates contents of the static `buffer` to `line` using 
 *   `str_strcat_realloc`.
 * - If a newline is found in `buffer`, it breaks out of the loop to process 
 *   the line.
 * - On read errors or end-of-file without data, it returns NULL if no 
 *   characters have been read; otherwise, it returns the partial line.
 * - Once a complete line is read, it truncates `line` up to and including the 
 *   newline using `str_replace_sub`.
 * - Adjusts the static `buffer` to remove the returned line by slicing off the 
 *   consumed part using `str_slice`.
 *
 * NOTE: The returned string is dynamically allocated and should be freed by 
 *       the caller when no longer needed.
 *
 * @param[in] fd The file descriptor from which to read the next line.
 *
 * @return A pointer to a newly allocated string containing the next line 
 *         from the file descriptor, including the newline character if found. 
 *         Returns NULL if no more lines can be read or if an error occurs.
 */
char	*gnl_get_next_line(int fd);

#endif
