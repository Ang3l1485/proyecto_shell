/**
 * @file commands.h
 * @brief Interfaz para los comandos del sistema.
 * 
 * Define las funciones que implementan la lógica de cada comando disponible
 * en la shell. Todas siguen la firma `void cmd_nombre(char **args)`.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

// --- Prototipos de Comandos ---

/**
 * @brief Lista los archivos del directorio actual.
 */
void cmd_listar(char **args);

/**
 * @brief Lee y muestra el contenido de un archivo.
 */
void cmd_leer(char **args);

/**
 * @brief Muestra la hora del sistema.
 */
void cmd_tiempo(char **args);

/**
 * @brief Realiza operaciones matemáticas simples.
 */
void cmd_calc(char **args);

/**
 * @brief Muestra la lista de ayuda.
 */
void cmd_ayuda(char **args);

/**
 * @brief Termina la ejecución de la shell.
 */

void cmd_salir(char **args);

void cmd_crear(char **args);
/**
 * @brief crea un archivo
 */

void cmd_buscar(char **args);
/**
 * @brief busca texto en un archivo
 */

void cmd_eliminar(char **args);
/**
 * @brief elimina un archivo
 */

void cmd_mover(char **args);
/**
 * @brief Mueve un archivo de ubicacion
 */

// --- Utilidades del Registro de Comandos ---

/**
 * @brief Retorna el número total de comandos registrados.
 * @return int Cantidad de comandos.
 */
int num_comandos();



#endif
