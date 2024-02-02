/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:33:15 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/02 12:36:15 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_init_node(t_gnl_list **pnt_l)
{
	char	*pnt;
	size_t	i;

	if (*pnt_l)
		return (1);
	*pnt_l = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!*pnt_l)
		return (0);
	pnt = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!pnt)
	{
		free(*pnt_l);
		*pnt_l = (void *)0;
		return (0);
	}
	(*pnt_l)->data = pnt;
	(*pnt_l)->next = (void *)0;
	(*pnt_l)->size = 0;
	i = 0;
	while (i++ < BUFFER_SIZE + 1)
		*pnt++ = '\0';
	return (1);
}

size_t	gnl_nl(const char *s)
{
	int	count;

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
