#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int errAtoi(const char *str) {
    char *endptr;
    int result = strtol(str, &endptr, 10);

    if (*endptr != '\0') {
        return -1; 
    }

    return result;
}

void printError(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

int myExit(ShellInfo *info) {
    if (info->argv[1]) {
        int exitCheck = errAtoi(info->argv[1]);
        if (exitCheck == -1) {
            info->status = 2;
            printError("Illegal number");
            fprintf(stderr, "%s\n", info->argv[1]);
            return 1;
        }
        info->err_num = exitCheck;
        return -2;
    }

    info->err_num = -1;
    return -2;
}

int myCd(ShellInfo *info) {
    char *s, *dir, buffer[1024];
    int chdirRet;

    s = getcwd(buffer, 1024);
    if (!s) {
        printError("getcwd failure");
    }

    if (!info->argv[1]) {
        dir = getenv("HOME");
        if (!dir) {
            chdirRet = chdir((dir = getenv("PWD")) ? dir : "/");
        } else {
            chdirRet = chdir(dir);
        }
    } else if (strcmp(info->argv[1], "-") == 0) {
        if (!getenv("OLDPWD")) {
            printf("%s\n", s);
            return 1;
        }

        printf("%s\n", getenv("OLDPWD"));
        chdirRet = chdir((dir = getenv("OLDPWD")) ? dir : "/");
    } else {
        chdirRet = chdir(info->argv[1]);
    }

    if (chdirRet == -1) {
        printError("can't cd to");
        fprintf(stderr, "%s\n", info->argv[1]);
    } else {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", getcwd(buffer, 1024), 1);
    }

    return 0;
}

int myHelp(ShellInfo *info) {
    char **argArray;

    argArray = info->argv;
    printf("help call works. Function not yet implemented\n");

    if (*argArray) {
        printf("%s\n", *argArray);
    }

    return 0;
}

int main() {
    
    ShellInfo info;
    char *arguments[] = { "command", "argument", NULL };
info.argv = arguments;


    printf("myExit status: %d\n", myExit(&info));
    printf("myCd status: %d\n", myCd(&info));
    printf("myHelp status: %d\n", myHelp(&info));

    return 0;
}

