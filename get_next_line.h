/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 08:30:04 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/08 14:14:28 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct s_gnl_list
{
	char				*data;
	struct s_gnl_list	*next;
	ssize_t				size;
}	t_gnl_list;
char	*get_next_line(int fd);
int		gnl_init_node(t_gnl_list **pnt_l);
size_t	gnl_nl(const char *s);

#endif
