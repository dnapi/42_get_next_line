#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#ifndef MAX_FD
#define MAX_FD 1024
#endif

typedef struct	s_str_list
{
	char	*data;
	struct s_str_list	*next;
	ssize_t	size;
//	struct s_str_list	*prev;
//	size_t	start;
//	size_t	end;
}	t_str_list;
char	*get_next_line(int fd);

#endif 

