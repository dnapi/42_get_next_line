#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	check_arguments(int argc);

int	main(int argc, char **argv)
{
	int	fd;
	char *pnt;

	fflush(stdout);
	printf("Buffer size=%d\n",BUFFER_SIZE);
	if (check_arguments(argc))
		return (1);
	fd = open(argv[1], O_RDONLY);
/*	if (fd == -1)
	{
		write(1, "Cannot read file.\n", 18);
		return (1);
	}
*/
	pnt = get_next_line(fd);
	close(fd);
	write(1, pnt, BUFFER_SIZE);
	write(1, "\n", 1);
	return (1);
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
