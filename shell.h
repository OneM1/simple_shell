#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64


char **parse_input(char *input);
char *find_command_in_path(char *cmd);
void execute_command(char **args);
int basic_command_execution(void);
int argument_handling(void);
int environment_variable_handling(void);
int exit_builtin_command(void);
int environment_builtin_command(void);

#endif 

