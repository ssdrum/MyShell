#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my-shell.h"


// Prototypes
void assign_out_stream(char **tokens);


void cd_in(char **args) {
    char cwd[MAX_BUFFER], nwd[MAX_BUFFER]; // Current and new working directory
    int is_changed;
    int num_tokens;

    num_tokens = array_len(args);
    if (num_tokens == 2) { // path was entered as argument
        strncpy(nwd, args[1], MAX_BUFFER); // Copies path passed as argument to nwd
        is_changed = chdir(nwd);
        if (is_changed == 0) { // chdir returns 0 if no error occurred
            getcwd(cwd, sizeof(cwd)); // Changes directory to the path in cwd
            setenv("PWD", cwd, 1); // Sets PWD environment variable to cwd
        } else {
            fputs("path does not exist\n", stdout); // Invalid path entered
        }
    } else if (num_tokens > 2) {
        fputs("cd: too many arguments\n", stdout); // Too many arguments passed to cd
    }
}


/*
 * Prints all environmental variables
 */
void environ_in() {
    extern char **environ;
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
}


/*
 * Implementation of echo commmand
 */
void echo_in(char **tokens) {
    int i = 1;
    while (tokens[i] != NULL) {
        printf("%s ", tokens[i++]);
    }
    printf("\n");
}


/*
 * Pauses shell until enter is pressed
 */
void pause_in() {
    char c;

    while(c != '\n') {
        c = fgetc(stdin);
    }
}

/*
 * TODO
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
*/
