/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:04:32 by yourLogin         #+#    #+#             */
/*   Updated: 2023/10/22 17:19:47 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	ft_display_file(int fd);
int		check_arguments(int argc);

int	main(int argc, char **argv)
{
	int	fd;

	if (check_arguments(argc))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Cannot read file.\n", 18);
		return (1);
	}
	ft_display_file(fd);
	close(fd);
	return (1);
}

void	ft_display_file(int fd)
{
	char	buffer;

	while (read(fd, &buffer, 1))
		write(1, &buffer, 1);
}

int	check_arguments(int argc)
{
	if (argc == 1)
	{
		write(1, "File name missing.\n", 19);
		return (1);
	}
	else if (argc > 2)
	{
		write(1, "Too many arguments.\n", 20);
		return (1);
	}
	else
		return (0);
}
