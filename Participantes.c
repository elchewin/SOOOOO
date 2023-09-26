#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main() {
    // Abre el FIFO en modo de escritura
    int fd = open("myfifo", O_WRONLY);

    if (fd == -1) {
        perror("Error al abrir el FIFO");
        exit(EXIT_FAILURE);
    }

    // Notifica que el participante está listo
    printf("Participante conectado.\n");

    // Cierra el FIFO
    close(fd);

    return 0;
}
