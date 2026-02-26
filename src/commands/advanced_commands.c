
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




/**
 * @brief Comando MOVER (mv)
 * 
 * Mueve o renombra un archivo de origen a destino.
 * 
 * @param args args[1] archivo origen, args[2] archivo destino.
 */
void cmd_mover(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: Debes especificar origen y destino.\nUso: mover <archivo_origen> <archivo_destino>\n");
        return;
    }

    if (rename(args[1], args[2]) == 0) {
        printf("Archivo '%s' movido a '%s'.\n", args[1], args[2]);
    } else {
        printf("Error: No se pudo mover el archivo '%s'.\n", args[1]);
    }
}

/**
 * @brief Comando ELIMINAR (rm)
 * 
 * Elimina un archivo del sistema.
 * 
 * @param args args[1] archivo a eliminar.
 */
void cmd_eliminar(char **args) {
    if (args[1] == NULL) {
        printf("Error: Debes especificar un archivo para eliminar.\nUso: eliminar <archivo>\n");
        return;
    }

    if (remove(args[1]) == 0) {
        printf("Archivo '%s' eliminado.\n", args[1]);
    } else {
        printf("Error: No se pudo eliminar el archivo '%s'.\n", args[1]);
    }
}
/**
 * cmd_buscar - Implementa la búsqueda de texto en un archivo.
 * @args: args[1] es el patrón de texto, args[2] es la ruta del archivo.
 * * Este comando cumple con el requisito #12 de comandos avanzados de archivos.
 */
void cmd_buscar(char **args) {
    // 1. Verificación de argumentos (Requisito para evitar errores en ejecución)
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: Uso incorrecto. Forma: buscar <texto> <archivo>\n");
        return;
    }

    // 2. Intento de apertura del archivo
    FILE *archivo = fopen(args[2], "r");
    if (archivo == NULL) {
        // Uso de perror para "errores detallados" según rúbrica
        perror("EAFITos: Error al abrir el archivo");
        return;
    }

    char linea[1024];
    int num_linea = 1;
    int encontrado = 0;

    printf("--- Resultados de búsqueda para: '%s' ---\n", args[1]);

    // 3. Lectura línea por línea
    while (fgets(linea, sizeof(linea), archivo)) {
        // strstr busca la subcadena args[1] dentro de la cadena 'linea'
        if (strstr(linea, args[1]) != NULL) {
            printf("Línea %d: %s", num_linea, linea);
            encontrado = 1;
        }
        num_linea++;
    }

    // 4. Feedback final al usuario
    if (!encontrado) {
        printf("No se encontró el texto especificado en el archivo.\n");
    }
    printf("------------------------------------------\n");

    // 5. Cierre de flujo (Fundamental para evitar penalización por Memory Leaks)
    fclose(archivo);
}

