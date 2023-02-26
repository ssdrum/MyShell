#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my-shell.h"


// Prototypes
void assign_out_stream(char **tokens);

/* 
* calls chdir with the argument as path
*     if return value of chdir is 0:
*         a) Change current dir with chdir
*         b) get current dir with getdir
*         c) Change PWD environment variable to new directory
*     else:
*         display error message
* */
char *change_dir(char **args) {
    char *cwd = malloc(sizeof(char) * 1024);
    int is_changed;
    char *new_dir;
    int num_tokens;

    getcwd(cwd, sizeof(cwd)); // Assigns absolute path of current working directory to cwd
    num_tokens = array_len(args);
    if (num_tokens == 2) { // path was entered as argument
        new_dir = args[1];
        is_changed = chdir(new_dir);
        if (is_changed == 0) { // chdir returns 0 if no error occurred
            setenv("PWD", cwd, 1); // Sets PWD environment variable to cwd
            getcwd(cwd, sizeof(cwd)); // Changes directory to the path in cwd
        } else {
            fputs("path does not exist\n", stdout); // Invalid path entered
        }
    } else if (num_tokens > 2) {
        fputs("cd: too many arguments\n", stdout); // Too many arguments passed to cd
    }

    return cwd;
}


/*
 * Prints all environmental variables
 */
void print_environ() {
    extern char **environ;

    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
}


void echo(char **tokens) {

    int i = 1;
    while (tokens[i] != NULL) {
        printf("%s ", tokens[i++]);
    }
    printf("\n");
}


void assign_out_stream(char **tokens) {
    int i;
    for (i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], ">") == 0) {
            freopen(tokens[i + 1], "w", stdout);
        } else if (strcmp(tokens[i], ">>") == 0) {
            freopen(tokens[i + 1], "a", stdout);
        }
    }
}
