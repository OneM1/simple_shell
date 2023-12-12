#include "shell.h"


/**
 * main - Entry point for a basic shell that executes single commands.
 *
 * Return: Exit status.
 */


int basic_command_execution(){
    char *buffer = NULL;
    size_t bufsize = 0;
    char *args[2]; 

    while (1) {
        printf("$ ");
        getline(&buffer, &bufsize, stdin);

        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) continue;

        args[0] = buffer; 
        args[1] = NULL;

        execute_command(args);
    }

    free(buffer);
    return 0;
}
