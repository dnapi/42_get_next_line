/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:26:33 by apimikov          #+#    #+#             */
/*   Updated: 2023/12/13 16:23:00 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

t_str_list	*read_once(int fd);
char		*read_line(int fd, t_str_list **buffer);
char		*mk_str_buf(t_str_list **buffer, size_t len);
int		init_node(t_str_list **pnt_l);
int		delete_list(t_str_list **buffer);
size_t		nl_pos(const char *s);

char	*get_next_line(int fd)
{
	static t_str_list	*buffer[MAX_FD];
	char *pnt;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return ((void *)0);
	if (!init_node(&buffer[fd]))
		return ((void *)0);
	pnt = read_line(fd, &buffer[fd]);
	//if pnt == NULL clean everything!
	delete_list(&buffer[fd]);
	return (pnt);
}

int	delete_list(t_str_list **buffer)
{
	t_str_list	*node_curr;
	t_str_list	*node_temp;
	
	node_curr = (*buffer)->next;
	(*buffer)->next = (void *)0;
	if ((*buffer)->size <= 0)
	{
		free((*buffer)->data);
		free(*buffer);
		*buffer = (void *)0;
	}
	while (node_curr)
	{
		free(node_curr->data);
		node_temp = node_curr->next;
		node_curr->next = (void *)0;
		free(node_curr);
		node_curr = (void *)0;
		node_curr = node_temp;
	}
	return (1);
}


char *mk_str_buf(t_str_list **buffer, size_t len)
{
	t_str_list	*curr_buf;
	char		*pnt;
	char		*pnt_node;
	size_t		i;

	if (!len)
		return ((void *)0);
	curr_buf = *buffer;
	i = 0;
	pnt = (char *)malloc((len + 1) * sizeof(char));
	if (!pnt)
		return ((void *)0);
	while (curr_buf)
	{
		pnt_node = curr_buf->data;
		while (i < len && *pnt_node)
			*(pnt + (i++)) = *pnt_node++;
		curr_buf = curr_buf->next;
	}
	*(pnt + i) = '\0';
	i = 0;
	while (*pnt_node)
		*(((*buffer)->data) + (i++)) = *pnt_node++;
	*((*buffer)->data + i) = '\0';
	(*buffer)->size = i;
	return (pnt);
}


char	*read_line(int fd, t_str_list **buffer)
{
	t_str_list	*curr_buffer;
	t_str_list	*next_buffer;
	size_t	pos;
	size_t	len;
	char	*pnt;

	curr_buffer = *buffer;
	pos = nl_pos(curr_buffer->data);
	len = (!pos) * curr_buffer->size + pos;
	while ((curr_buffer == *buffer && !pos) || (pos == 0
	       && curr_buffer->size == BUFFER_SIZE)) // will not read last time
	{
		next_buffer = read_once(fd);
		if (!next_buffer)  // clean list ??? here ove in get_next_line?
			return ((void *)0);
		if (next_buffer->size == -1) //this (if () {})  can be deleted !
		{
//			printf("read -> 0\n");
			free(next_buffer->data);
			free(next_buffer);
			break;
		}
		curr_buffer->next = next_buffer;
		curr_buffer = next_buffer;
		pos = nl_pos(curr_buffer->data);
		len = len + (!pos) * curr_buffer->size + (pos > 0) * pos;
	}
	pnt = mk_str_buf(buffer, len);
	return (pnt);
}

t_str_list	*read_once(int fd)
{
	t_str_list	*pnt_l;
	ssize_t		len;

	pnt_l = (void *)0;
	init_node(&pnt_l);
	len = read(fd, pnt_l->data, BUFFER_SIZE);
	if (len < 0)
	{
		free(pnt_l->data);
		free(pnt_l);
		return ((void *)0);
	}
	*(pnt_l->data + BUFFER_SIZE) = '\0';
	pnt_l->size = len + (!len) * (-1);
	return (pnt_l);
}


int	init_node(t_str_list **pnt_l)
{
	char	*pnt;
	size_t	i;

	if (*pnt_l)
		return (1);
	*pnt_l = (t_str_list *)malloc(sizeof(t_str_list));
	if (!*pnt_l)
		return (0);
	pnt = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!pnt)
	{
		free(*pnt_l);
		return (0);
	}
	(*pnt_l)->data = pnt;
	(*pnt_l)->next = (void *)0;
	(*pnt_l)->size = 0;
	i = 0; // is it needed to put all to \0
	while (i++ < BUFFER_SIZE + 1)
		*pnt++ = '\0';
	return (1);
}

/*
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
*/

size_t	nl_pos(const char *s)
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
