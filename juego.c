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
    if (mkfifo("/tmp/lectura", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("No se pudo crear FIFO\n");
            return 1;
        }
    }
    // creacion del FIFO
    if (mkfifo("/tmp/escritura", 0777) == -1)
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

    // Abre el FIFO (lectura)
    int fdR = open("/tmp/rw", O_RDONLY);

    int buf, num_participantes_t = num_participantes;

    // Espera a que se conecten todos los participantes
    while (num_participantes_t != 0)
    {
        read(fdR, buf, sizeof(buf));
        printf("Esperando que se conecten %d participantes...\n", num_participantes_t);
        buf -= num_participantes_t;
        sleep(1); // Puedes ajustar este valor según tus necesidades
    }
    printf("¡Todos los participantes están conectados!\n");
    // Cierra el FIFO
    close(fdR);

    return 0;
}
