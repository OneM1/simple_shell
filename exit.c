#include "shell.h"


/**
 * main - Entry point for a shell that implements the 'exit' command.
 *
 * Return: Exit status.
 */


int exit_builtin_command() {
    char *buffer = NULL;
    size_t bufsize = 0;
    char **args;

    while (1) {
        printf("$ ");
        getline(&buffer, &bufsize, stdin);

        args = parse_input(buffer);

        if (strcmp(args[0], "exit") == 0) {
            free(args);
            break;
        }

        execute_command(args);
        free(args);
    }

    free(buffer);
    return 0;
}

