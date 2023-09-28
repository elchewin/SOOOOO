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
    mkfifo("mi_fifo", 0666);

    int buf, fd, n;

    int num_participantes;
    printf("Ingrese el número de participantes: ");
    scanf("%d", &num_participantes);

    for (int i = 0; i < num_participantes; i++)
    {
        fd = open("mi_fifo", O_RDONLY);
        n = read(fd, &buf, sizeof(int));

        printf("Nr bytes rx: %d\n", n);
        printf("RX mensaje: %d\n", buf);

        close(fd);
    }

    return 0;
}