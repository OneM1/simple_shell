#include "shell.h"

int execute(char **args) {
    if (args[0] == NULL) {
        
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return shell_exit(args);
    }

    if (strcmp(args[0], "env") == 0) {
        return shell_env(args);
    }

    return launch(args);
}

int launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        
        perror("shell");
    } else {
        
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

