/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:26:33 by apimikov          #+#    #+#             */
/*   Updated: 2023/12/12 16:25:13 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

t_str_list	*read_once(int fd);
t_str_list	*read_line(int fd, t_str_list **buffer);
t_str_list	*init_node(void);
int	nl_position(const char *s);

char	*get_next_line(int fd)
{
	static t_str_list	*buffer[MAX_FD];
	char		*pnt;
	size_t		size;
	size_t		i;
	t_str_list	*node;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return ((void *)0);
//	node = read_once(fd);
//	return (node->data);
//  remove stdio
//	printf("fd = %d, &buffer[%d] = %p, NULL= %p\n", fd, fd, &buffer[fd], NULL);
	node = read_line(fd, &buffer[fd]);
	return (node->data);
}

t_str_list	*read_line(int fd, t_str_list **buffer)
{
	t_str_list	*curr_buffer;
	t_str_list	*next_buffer;
//	int		i;
//	char	c;
	size_t	position;
	size_t len;

//	i = 0;
	curr_buffer = *buffer;
	if (!curr_buffer)
		curr_buffer = init_node();
	position = nl_position(curr_buffer->data);
	len = curr_buffer->size;

//	write(1, "num=0\n", 6);
//	write(1, curr_buffer->data, BUFFER_SIZE + 1); 
//	write(1, "end\n", 4);
	while (!position)
	{
		next_buffer = read_once(fd);
		curr_buffer->next = next_buffer;
		curr_buffer = next_buffer;
		position = nl_position(curr_buffer->data);
		len = len + curr_buffer->size;
//		c = '0' + i;
//		write(1, &c, 1);
//		write(1, next_buffer->data, BUFFER_SIZE + 1); 
//		write(1, "\n" , 1);
	}
	printf("len = %zu",len);
	return (curr_buffer);
}


t_str_list	*read_once(int fd)
{
	t_str_list	*pnt_l;
	size_t		len;

	pnt_l = init_node();	
	len = read(fd, pnt_l->data, BUFFER_SIZE);
	if (len == -1)
	{
		free(pnt_l->data);
		pnt_l->data = NULL;
		free(pnt_l);
		return ((void *)0);
	}
	*(pnt_l->data + BUFFER_SIZE) = '\0';
	pnt_l->next = NULL;
	pnt_l->size = len;
	return (pnt_l);
}

t_str_list	*init_node(void)
{
	t_str_list	*pnt_l;
	char		*pnt;

	pnt_l = (t_str_list *)malloc(sizeof(t_str_list));
	if (!pnt_l)
		return ((void *)0);
	pnt = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!pnt)
	{
		free(pnt_l);
		return ((void *)0);
	}
	*pnt = '\0';
	pnt_l->data = pnt;
	pnt_l->next = (void *)0;
	pnt_l->size = 0;
	return (pnt_l);
}


int	nl_position(const char *s)
{
	int count;

	count = 1;
    while (*s)
    {
        if (*s == '\n')
            return (count);
        s++;
		count++;
    }
	return (0);
}
