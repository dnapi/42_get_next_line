/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:26:33 by apimikov          #+#    #+#             */
/*   Updated: 2023/12/15 08:39:26 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_once(int fd, t_gnl_list **pnt_l);
char	*read_line(int fd, t_gnl_list **buffer);
char	*mk_str_buf(t_gnl_list **buffer, size_t len);
int		delete_list(t_gnl_list **buffer);

char	*get_next_line(int fd)
{
	static t_gnl_list	*buffer[OPEN_MAX];
	char				*pnt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return ((void *)0);
	if (!gnl_init_node(&buffer[fd]))
		return ((void *)0);
	pnt = read_line(fd, &buffer[fd]);
	if (!pnt)
		buffer[fd]->size = -1;
	delete_list(&buffer[fd]);
	return (pnt);
}

int	delete_list(t_gnl_list **buffer)
{
	t_gnl_list	*node_curr;
	t_gnl_list	*node_temp;

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

char	*mk_str_buf(t_gnl_list **buffer, size_t len)
{
	t_gnl_list	*curr_buf;
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
	while (*pnt_node)
		*(((*buffer)->data) + (i++) - len) = *pnt_node++;
	*((*buffer)->data + i - len) = '\0';
	(*buffer)->size = i - len;
	return (pnt);
}

char	*read_line(int fd, t_gnl_list **buffer)
{
	t_gnl_list	*curr_buf;
	t_gnl_list	*next_buf;
	size_t		pos;
	size_t		len;
	char		*pnt;

	curr_buf = *buffer;
	pos = gnl_nl(curr_buf->data);
	len = (!pos) * curr_buf->size + pos;
	while ((!pos) && (curr_buf == *buffer || curr_buf->size == BUFFER_SIZE))
	{
		pos = read_once(fd, &next_buf);
		if (!pos)
			return ((void *)0);
		if (pos == 2)
			break ;
		curr_buf->next = next_buf;
		curr_buf = next_buf;
		pos = gnl_nl(curr_buf->data);
		len = len + (!pos) * curr_buf->size + (pos > 0) * pos;
	}
	pnt = mk_str_buf(buffer, len);
	return (pnt);
}

int	read_once(int fd, t_gnl_list **pnt_l)
{
	ssize_t		len;

	*pnt_l = (void *)0;
	if (!gnl_init_node(pnt_l))
		return (0);
	len = read(fd, (*pnt_l)->data, BUFFER_SIZE);
	if (len < 0)
	{
		free((*pnt_l)->data);
		free(*pnt_l);
		return (0);
	}
	*((*pnt_l)->data + BUFFER_SIZE) = '\0';
	(*pnt_l)->size = len + (!len) * (-1);
	if (!len)
	{
		free((*pnt_l)->data);
		free(*pnt_l);
		return (2);
	}
	return (1);
}
