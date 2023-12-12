#include "shell.h"


/**
 * main - Entry point for a shell that handles command arguments.
 *
 * Return: Exit status.
 */

int argument_handling() {
    char *buffer = NULL;
    size_t bufsize = 0;
    char **args;

    while (1) {
        printf("$ ");
        getline(&buffer, &bufsize, stdin);

        args = parse_input(buffer);
        execute_command(args);

        free(args);
    }

    free(buffer);
    return 0;
}

