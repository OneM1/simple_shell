#include "shell.h"

char **parse_input(char *input) {
    int position = 0;
    char **tokens;
    char *token;

    tokens = malloc(MAX_ARGS * sizeof(char*));
    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \t\r\n\a");
    while (token != NULL) {
        tokens[position++] = token;
        if (position >= MAX_ARGS) {
            position = MAX_ARGS - 1;
            break;
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

char *find_command_in_path(char *cmd) {
    char *path, *path_copy, *token, *full_path;
    struct stat st;

    path = getenv("PATH");
    path_copy = strdup(path);
    full_path = malloc(BUFFER_SIZE * sizeof(char));

    token = strtok(path_copy, ":");
    while (token != NULL) {
        snprintf(full_path, BUFFER_SIZE, "%s/%s", token, cmd);
        if (stat(full_path, &st) == 0) {
            free(path_copy);
            return full_path;
        }
        token = strtok(NULL, ":");
    }

    free(path_copy);
    free(full_path);
    return NULL;
}

void execute_command(char **args) {
    pid_t pid;
    int status;
    char *command_path;

    command_path = find_command_in_path(args[0]);
    if (command_path == NULL) {
        printf("%s: command not found\n", args[0]);
        return;
    }

    pid = fork();
    if (pid == 0) {
        if (execv(command_path, args) == -1) {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Error");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(command_path);
}

