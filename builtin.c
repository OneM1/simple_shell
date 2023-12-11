#include "shell.h"

int shell_exit(char **args) {
    return 0;
}

int shell_env(char **args) {
    for (char **env = environ; *env != 0; env++) {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
    }
    return 1;
}

