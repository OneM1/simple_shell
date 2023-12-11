#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CMD_LEN 100
#define PROMPT "#cisfun$ "

/**
 * main - Entry point for the simple shell
 */
int main(void)
{
    char command[MAX_CMD_LEN];
    pid_t pid;
    int status;

    while (1) {
        printf(PROMPT); 

        
        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) {
            if (feof(stdin)) { 
                printf("\n");
                break;
            } else {
                continue; /
            }
        }

        
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        
        pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        }

        if (pid == 0) { // Child process
            
            execlp(command, command, NULL);

            
            printf("./shell: %s: No such file or directory\n", command);
	    exit(EXIT_FAILURE);
        } else { 
 waitpid(pid, &status, 0);
        }
    }

return 0;
}

