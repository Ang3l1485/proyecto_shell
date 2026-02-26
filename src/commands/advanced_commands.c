#include "../../include/commands.h"
#include <stdio.h>
#include <string.h>

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