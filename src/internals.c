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
    char *dir = args[1];
    int is_changed;

    if (num_tokens == 1) {
        is_changed = chdir(dir);
        if (is_changed == 0) { // chdir returns 0 if no error occurred
            getcwd(cwd, sizeof(cwd)); // Changes directory to the path in cwd
            setenv("PWD", cwd, 1); // Sets PWD environment variable to cwd
        } else {
            printf("path does not exist\n"); // Invalid path entered
        }
    } else if (num_tokens > 1) {
        printf("cd: too many arguments\n");
    }

    printf("CWD: %s\n", cwd); // Print cwd
}
