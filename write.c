#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> // Incluye la cabecera para memcpy

int main()
{
    int x = 1;

    int fd = open("mi_fifo", O_WRONLY);
    write(fd, &x, sizeof(int));

    close(fd);

    pid_t pid;

    return 0;
}