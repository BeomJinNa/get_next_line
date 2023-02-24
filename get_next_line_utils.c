/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:18:17 by bena              #+#    #+#             */
/*   Updated: 2023/02/24 15:27:24 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

char	*init_buffer(int buffer_size)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * buffer_size);
	if (output == NULL)
		return (NULL);
	while (buffer_size-- > 0)
		output[buffer_size] = '\0';
	return (output);
}

int	does_newline_exist(char *str, char **output)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr++ == '\n')
		{
			if (output != NULL)
				*output = ptr;
			return (1);
		}
	}
	if (output != NULL)
		*output = ptr;
	return (0);
}

char	*find_end_position(char *str)
{
	char	*output;

	output = str;
	while (*output)
		output++;
	return (output);
}

char	*extend_buffer(char *buf, int *size, char **used, char **ptr)
{
	char	*new_buffer;
	char	*from;
	char	*to;

	*size = ((*size - 1) << 1) + 1;
	new_buffer = init_buffer(*size);
	if (new_buffer == NULL)
	{
		free(buf);
		return (NULL);
	}
	from = buf;
	to = new_buffer;
	while (*from)
		*to++ = *from++;
	*used = new_buffer + (*used - buf);
	*ptr = new_buffer + (*ptr - buf);
	free(buf);
	return (new_buffer);
}

void	set_pointers(char **ptr, void *address, int size)
{
	if (ptr[OPEN_MAX] != NULL)
		return ;
	while (size-- > 0)
		*(ptr++) = address;
}
