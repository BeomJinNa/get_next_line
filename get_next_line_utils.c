/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:18:17 by bena              #+#    #+#             */
/*   Updated: 2023/02/26 19:39:54 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	does_newline_exist_gnl(t_buf *node)
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

char	*create_buffer_gnl(size_t size)
{
	if (size <= 1)
		return (NULL);
	return ((char *)malloc(sizeof(char) * size));
}
