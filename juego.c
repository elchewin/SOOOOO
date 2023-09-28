#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    // creacion del FIFO
    if (mkfifo("FIFO", 0666) == -1)
    {
        if (errno != EEXIST)
        {
            printf("No se pudo crear FIFO\n");
            return 1;
        }
    }

    int fdW = open("/output/FIFO", O_WRONLY);

    // indico numero inicial de jugadores
    int buf = 0;
    write(fdW, buf, sizeof(buf));

    close(fdW);

    int num_participantes;
    printf("Ingrese el número de participantes: ");
    scanf("%d", &num_participantes);

    // Abre el FIFO (lectura)
    int fdR = open("/output/FIFO", O_RDONLY);

    // Espera a que se conecten todos los participantes
    while (1)
    {
        read(fdR, buf, sizeof(buf));
        printf("hola %d", buf);
        close(fdR);

        if (buf != num_participantes)
        {
            printf("Esperando que se conecten %d participantes...\n", num_participantes - buf);
        }
        else
        {
            break;
        }

        sleep(2); // Puedes ajustar este valor según tus necesidades
    }
    close(fdR);
    printf("¡Todos los participantes están conectados!\n");
    // Cierra el FIFO

    return 0;
}
