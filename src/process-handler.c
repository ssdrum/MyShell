#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my-shell.h"


// Prototypes
void assign_streams(char **tokens);


/*
 * char **tokens: Array strings
 * Handles forking and execution of non-internal commands. Creates a child
 * process which executes the command passed in tokens[0]. Also, reassigns
 * I/O file descriptors if the user is redirecting them.
 */
void fork_exec(char **tokens) {
    // TODO: Implement &
    pid_t pid;
    int pid_status, last_arg, bg_exec;
    char **parsed_args;

    bg_exec = 0;
    pid = fork(); // Creates child process
    if (pid == 0) {  // Child process
        last_arg = get_last_arg(tokens);
        parsed_args = trim_arr(tokens, last_arg);

        assign_streams(tokens); // Redirect stdin and/or stdout if necessary

        if (execvp(parsed_args[0], parsed_args) == -1) { // Executes command in child process
            fprintf(stderr, "command not found: %s\n", tokens[0]);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {  // Child process was not created
        fprintf(stderr, "cannot create child process\n");
        exit(EXIT_FAILURE);
    } else { // parent process
        waitpid(pid, &pid_status, 0);
    }
}


/**
 * Redirects stdin and stdout if necessary
 */
void assign_streams(char **tokens) {
    int i;
    for (i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            if (freopen(tokens[i + 1], "r", stdin) == NULL) {
                fprintf(stderr, "no such file or directory: %s\n", tokens[i + 1]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(tokens[i], ">") == 0) {
            if (freopen(tokens[i + 1], "w", stdout) == NULL) {
                fprintf(stderr, "cannot open file: %s\n", tokens[i + 1]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(tokens[i], ">>") == 0) {
            if (freopen(tokens[i + 1], "a", stdout) == NULL) {
                fprintf(stderr, "cannot open file: %s\n", tokens[i + 1]);
                exit(EXIT_FAILURE);
            }
        }
    }
}
