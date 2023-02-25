/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:18:17 by bena              #+#    #+#             */
/*   Updated: 2023/02/26 16:00:07 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	does_newline_exist(t_buf *node)
{
	while (node->scanner < node->buf_end)
		if (*node->scanner++ == '\n')
			return (1);
	return (0);
}

char	*remove_node_gnl(t_buf **node_ptr)
{
	t_buf	*node;

	node = *node_ptr;
	node->before->next = node->next;
	if (node->next != NULL)
		node->next->before = node->before;
	if (node->buf != NULL)
		free(node->buf);
	free(node);
	*node_ptr = NULL;
	return (NULL);
}

void	extend_buffer(t_buf *node)
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
