#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

//valgrind --tool=memcheck <your_app> <your_apps_params>

int	check_arguments(int argc);

int	main(int argc, char **argv)
{
	int	fd;
	char *pnt;

	printf("Buffer size=%d\n",BUFFER_SIZE);
	fflush(stdout);
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
	printf("1st line \n\t->%s<-\n",pnt);
//	close(fd);
//	fd =100;
	pnt = get_next_line(fd);
	printf("2nd line \n\t->%s<-\n",pnt);
	pnt = get_next_line(fd);
	printf("3nd line \n\t->%s<-\n",pnt);
	pnt = get_next_line(fd);
	printf("4th line \n\t->%s<-\n",pnt);
//	read(fd, pnt, 10);
//	printf("read result ->%s<-\n",pnt);
	close(fd);
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
