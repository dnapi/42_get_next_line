#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file_one_line.txt", O_RDONLY);
    char *buffer=calloc(20,1);

    int  bytesRead = read(fd, buffer, 15);

//	write(1,buffer, 12);

		
    printf("\n9,10,11 = %d,%d,%d\n",(int)buffer[9],(int)buffer[10],(int)buffer[11]);
    printf("\n4,5,6 = %d,%d,%d\n",(int)buffer[4],(int)buffer[5],(int)buffer[6]);
    printf("bytesRead=%d\n", bytesRead);
//	fflush(stdout);
    close(fd);
    return 0;
}

