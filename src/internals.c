#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my-shell.h"

/* 
* calls chdir with the argument as path
*     if return value of chdir is 0:
*         a) Change current dir with chdir
*         b) get current dir with getdir
*         c) Change PWD environment variable to new directory
*     else:
*         display error message
* */
void change_dir(char **args, int num_tokens) {
    char cwd[512];
    int is_changed;
    char *new_dir;

    getcwd(cwd, sizeof(cwd)); // Assigns absolute path of current working directory to cwd

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

    printf("CWD: %s\n", cwd); // Prints cwd
}
