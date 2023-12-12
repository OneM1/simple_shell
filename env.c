#include "shell.h"


/**
 * main - Entry point for a shell that can display environment variables.
 *
 * Return: Exit status.
 */


extern char **environ; 

int environment_builtin_command() {
    char *buffer = NULL;
    size_t bufsize = 0;
    char **args;
    char **env; 

    while (1) {
        printf("$ ");
        getline(&buffer, &bufsize, stdin);

        args = parse_input(buffer);

        if (strcmp(args[0], "exit") == 0) {
            free(args);
            break;
        } else if (strcmp(args[0], "env") == 0) {
            for (env = environ; *env != NULL; env++) {
                printf("%s\n", *env);
            }
        } else {
            execute_command(args);
        }

        free(args);
    }

    free(buffer);
    return 0;
}

