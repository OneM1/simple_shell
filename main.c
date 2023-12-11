#include "shell.h"

int main(int argc, char **argv) {
    /* Load config files, if any */

    /* Run command loop */
    loop();

    /* Perform any shutdown/cleanup */

    return EXIT_SUCCESS;
}

void loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("#cisfun$ ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);
}

