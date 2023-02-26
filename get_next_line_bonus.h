/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:17:46 by bena              #+#    #+#             */
/*   Updated: 2023/02/26 19:17:18 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buf
{
	char			is_this_dynamic;
	char			*buf;
	char			*buf_end;
	char			*scanner;
	ssize_t			read_bytes;
	int				buf_size;
	int				fd;
	struct s_buf	*next;
	struct s_buf	*before;
}					t_buf;

char			*get_next_line(int fd);
#endif
