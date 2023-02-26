/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:17:38 by bena              #+#    #+#             */
/*   Updated: 2023/02/26 19:40:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*remove_node_gnl(t_buf **node_ptr);
int				does_newline_exist_gnl(t_buf *node);
char			*create_buffer_gnl(size_t size);
static t_buf	*get_node(int fd, t_buf *node);
static char		*release_node(t_buf *node);
static char		*extract_one_line(t_buf *node);
static void		extend_buffer(t_buf *node);

char	*get_next_line(int fd)
{
	static t_buf	list;
	t_buf			*node;

	node = get_node(fd, &list);
	if (node == NULL)
		return (NULL);
	node->scanner = node->buf;
	while (does_newline_exist_gnl(node) == 0)
	{
		if (node->buf_size < (node->buf_end - node->buf) + BUFFER_SIZE + 1)
			extend_buffer(node);
		if (node == NULL)
			return (NULL);
		node->read_bytes = read(fd, node->buf_end, BUFFER_SIZE);
		node->buf_end += node->read_bytes;
		if (node->read_bytes < BUFFER_SIZE)
			return (release_node(node));
	}
	return (extract_one_line(node));
}

static t_buf	*get_node(int fd, t_buf *node)
{
	while (node->next != NULL && (node->fd != fd || node->is_this_dynamic == 0))
		node = node->next;
	if (node->fd == fd && node->is_this_dynamic == 1)
		return (node);
	node->next = (t_buf *)malloc(sizeof(t_buf));
	if (node->next == NULL)
		return (NULL);
	node->next->buf = create_buffer_gnl(BUFFER_SIZE + 1);
	if (node->next->buf == NULL)
		return ((t_buf *)remove_node_gnl(&node->next));
	(node->next)->before = node;
	node = node->next;
	node->buf_end = node->buf;
	node->scanner = node->buf;
	node->buf_size = BUFFER_SIZE + 1;
	node->fd = fd;
	node->next = NULL;
	node->is_this_dynamic = 1;
	return (node);
}

static char	*release_node(t_buf *node)
{
	char	*output;

	if (node->read_bytes < 0)
		return (remove_node_gnl(&node));
	output = extract_one_line(node);
	if (output == NULL)
		return (NULL);
	return (output);
}

static char	*extract_one_line(t_buf *node)
{
	char	*new_buffer;
	char	*from;
	char	*to;
	size_t	length;

	length = 0;
	if (node->scanner > node->buf)
		if (*(node->scanner - 1) == '\n')
			length = node->scanner - node->buf;
	if (length == 0)
		does_newline_exist_gnl(node);
	if (length == 0)
		length = node->scanner - node->buf;
	new_buffer = create_buffer_gnl(length + 1);
	if (new_buffer == NULL)
		return (remove_node_gnl(&node));
	from = node->scanner;
	to = new_buffer + length;
	*to = '\0';
	while (length-- > 0)
		*--to = *--from;
	while (node->scanner < node->buf_end)
		*from++ = *node->scanner++;
	node->buf_end = from;
	return (new_buffer);
}

static void	extend_buffer(t_buf *node)
{
	char	*new_buffer;
	char	*from;
	char	*to;
	size_t	length;

	node->buf_size = ((node->buf_size - 1) << 1) + 1;
	new_buffer = (char *)malloc(sizeof(char) * node->buf_size);
	if (new_buffer == NULL)
	{
		remove_node_gnl(&node);
		return ;
	}
	from = node->buf;
	to = new_buffer;
	length = node->buf_end - node->buf;
	while (length-- > 0)
		*to++ = *from++;
	node->buf_end = new_buffer + (node->buf_end - node->buf);
	node->scanner = new_buffer + (node->scanner - node->buf);
	free(node->buf);
	node->buf = new_buffer;
}
