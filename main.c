#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char** environ; 

int main(int argc, char *argv[]) {
    char *input;
    size_t input_size = 0;
    size_t input_length;

    if (argc > 1) {
        
        FILE *input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            perror("Error opening input file");
            return EXIT_FAILURE;
        }

        input = NULL;

        while (getline(&input, &input_size, input_file) != -1) {
            
            input_length = strlen(input);
            if (input_length > 0 && input[input_length - 1] == '\n') {
                input[input_length - 1] = '\0';
            }

            
            printf("You entered: %s\n", input);
        }

        free(input);
        fclose(input_file);
    } else {
        
        input = NULL;

        while (1) {
            printf("($) ");
            getline(&input, &input_size, stdin);

            
            input_length = strlen(input);
            if (input_length > 0 && input[input_length - 1] == '\n') {
                input[input_length - 1] = '\0';
            }

            if (strcmp(input, "exit") == 0) {
                free(input);
                exit(0);
            }

           
            printf("You entered: %s\n", input);
        }

        free(input);
    }

    return 0;
}

