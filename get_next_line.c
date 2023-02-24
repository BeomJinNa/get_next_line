/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:17:38 by bena              #+#    #+#             */
/*   Updated: 2023/02/24 16:04:31 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static char	*end_of_file(char **buffer);
static char	*get_the_line(char **buffer, char *end_of_line);
char		*find_end_position(char *str);
char		*init_buffer(int buffer_size);
int			does_newline_exist(char *str, char **output);
char		*extend_buffer(char *buf, int *size, char **used, char **ptr);
void		set_pointers(char **ptr, void *address, int size);
static char	*remove_buffer(char **buffer);

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX + 1] = {NULL, };
	char		*buf_used;
	char		*ptr;
	int			buf_size;

	set_pointers(buf, (void *)&buf, OPEN_MAX + 1);
	buf_size = BUFFER_SIZE + 1;
	if (buf[fd] == (char *)&buf)
		buf[fd] = init_buffer(buf_size);
	if (buf[fd] == NULL)
		return (NULL);
	ptr = buf[fd];
	buf_used = find_end_position(buf[fd]);
	while (does_newline_exist(ptr, &ptr) == 0)
	{
		if (buf_size < (buf_used - buf[fd]) + (BUFFER_SIZE + 1))
			buf[fd] = extend_buffer(buf[fd], &buf_size, &buf_used, &ptr);
		if (buf[fd] == NULL)
			return (NULL);
		if (read(fd, buf_used, BUFFER_SIZE) < BUFFER_SIZE)
			if (does_newline_exist(ptr, NULL) == 0)
				return (end_of_file(&buf[fd]));
		buf_used = find_end_position(buf_used);
	}
	return (get_the_line(&buf[fd], ptr));
}

static char	*end_of_file(char **buffer)
{
	char	*from;
	char	*to;
	char	*new_buffer;
	size_t	length;

	new_buffer = *buffer;
	while (*new_buffer)
		new_buffer++;
	length = new_buffer - *buffer;
	if (length == 0)
		return (remove_buffer(buffer));
	new_buffer = (char *)malloc(sizeof(char) * (length + 1));
	if (new_buffer != NULL)
	{
		to = new_buffer;
		from = *buffer;
		while (*from)
			*to++ = *from++;
		*to = '\0';
	}
	free(*buffer);
	*buffer = NULL;
	return (new_buffer);
}

static char	*get_the_line(char **buffer, char *end_of_line)
{
	char	*new_buffer;
	char	*from;
	char	*to;
	size_t	length;
	char	*residue_buffer;

	length = end_of_line - *buffer;
	new_buffer = (char *)malloc(sizeof(char) * (length + 1));
	if (new_buffer != NULL)
	{
		to = new_buffer;
		from = *buffer;
		while (length-- > 0)
			*to++ = *from++;
		*to = '\0';
	}
	residue_buffer = init_buffer(BUFFER_SIZE + 1);
	to = residue_buffer;
	if (residue_buffer != NULL)
		while (*from)
			*to++ = *from++;
	free(*buffer);
	*buffer = residue_buffer;
	return (new_buffer);
}

static char	*remove_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}
