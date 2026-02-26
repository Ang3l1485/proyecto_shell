

#include <stdio.h>  // printf
#include "commands.h"
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * @brief Comando SALUDAR
 * 
 * Saluda al usuario con un mensaje personalizado.
 * Demuestra el uso de argumentos para personalizar la salida.
 * 
 * @param args Argumentos del comando (se espera un nombre).
 */

 void cmd_crear(char **args) {
    if (args[1] == NULL) {
        printf("debe ingresar un nombre de archivo\n");
        return;
    }

    int existed = 0;
    struct stat st;
    if (stat(args[1], &st) == 0) {
        existed = 1;
    } else if (errno != ENOENT) {
        printf("Error al verificar el archivo\n");
        return;
    }

    int fd = open(args[1], O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error al crear/abrir el archivo");
        return;
    }
    close(fd);

    if (utimensat(AT_FDCWD, args[1], NULL, 0) == -1) {
        perror("Error al actualizar timestamps");
        return;
    }

    if (existed) {
        printf("Archivo '%s' actualizado (timestamps)\n", args[1]);
    } else {
        printf("Archivo '%s' creado exitosamente..\n", args[1]);
    }
 }


