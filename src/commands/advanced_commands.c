/**
 * @file advanced_commands.c
 * @brief Comandos avanzados del sistema.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

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
