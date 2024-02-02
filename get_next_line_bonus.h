/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:33:41 by apimikov          #+#    #+#             */
/*   Updated: 2023/12/15 10:33:54 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
