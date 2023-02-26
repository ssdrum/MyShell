#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my-shell.h"


// Prototypes
void assign_streams(char **tokens);


/*
 * char **tokens: Array strings
 * int num_tokens: Number of elements in tokens
 * Handles forking and execution of non-internal commands. Creates a child
 * process which executes the command passed in tokens[0].
 */
void fork_exec(char **tokens) {
    // TODO: Implement &
    pid_t pid;
    char **parsed_args;
    int pid_status, exec_status, last_arg;

    pid = fork(); // Creates child process
    if (pid == 0) {  // Child process's id is 0
        last_arg = get_last_arg(tokens);
        parsed_args = trim_arr(tokens, last_arg);
        assign_streams(tokens); // Redirect stdin and/or stdout if necessary
        exec_status = execvp(parsed_args[0], parsed_args); // Executes command in child process
        if (exec_status == -1) { // execvp returns -1 if program passed is not found
            printf("command not found: %s\n", parsed_args[0]);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {  // Child process was not created
        fputs("cannot create child process", stdout);
        exit(EXIT_FAILURE);
    } else { // parent process
        waitpid(pid, &pid_status, 0); // Waits for child process to end. 0 means no flags
    }
}


/**
 * Redirects stdin and stdout if necessary
 */
void assign_streams(char **tokens) {
    int i;
    for (i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            freopen(tokens[i + 1], "r", stdin);
        } else if (strcmp(tokens[i], ">") == 0) {
            freopen(tokens[i + 1], "w", stdout);
        } else if (strcmp(tokens[i], ">>") == 0) {
            freopen(tokens[i + 1], "a", stdout);
        }
    }
}
