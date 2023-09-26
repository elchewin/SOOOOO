#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // creacion del FIFO
    if (mkfifo("myfifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("No se pudo crear FIFO\n");
            return 1;
        }
    }

    int num_participantes;
    printf("Ingrese el número de participantes: ");
    scanf("%d", &num_participantes);

    // Abre el FIFO en modo de lectura no bloqueante
    int fd = open("myfifo", O_RDWR | O_NONBLOCK);
    printf("Esperando que se conecten %d participantes...\n", num_participantes);

    // Espera a que se conecten todos los participantes
    while (1)
    {
        if (num_participantes == 0)
        {
            printf("¡Todos los participantes están conectados!\n");
            break;
        }
        sleep(1); // Puedes ajustar este valor según tus necesidades
    }

    // Cierra el FIFO
    close(fd);

    return 0;
}