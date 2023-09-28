#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int buf;

    // Proceso lectura
    int fdR = open("/output/FIFO", O_RDONLY);

    read(fdR, buf, sizeof(buf));

    printf("hay %d jugadores conectados antes que yo\n", buf);

    close(fdR);

    // Proceso Escritura
    int fdW = open("/output/FIFO", O_WRONLY);
    buf++;
    write(fdW, buf, sizeof(buf));
    // Notifica que el participante está listo
    printf("Participante conectado nª %d.\n", buf);

    close(fdW);

    return 0;
}