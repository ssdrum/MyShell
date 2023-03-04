#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "myshell.h"


/**
 * char **tokens: Array strings
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


/*
 * char **tokens: Array strings
 * Handles forking and execution of non-internal commands. Creates a child
 * process which executes the command passed in tokens[0]. Also, reassigns
 * I/O file descriptors if the user is redirecting them.
 */
void handle_ext_cmd(char **tokens) {
    // TODO: Implement &
    pid_t pid;
    int pid_status, last_arg;
    char **trimmed_tokens;

    pid = fork(); // Creates child process
    if (pid == 0) {  // Child process
        last_arg = get_last_arg(tokens);
        trimmed_tokens = trim_arr(tokens, last_arg);

        assign_streams(tokens); // Redirect stdin and/or stdout if necessary

        if (execvp(trimmed_tokens[0], trimmed_tokens) == -1) { // Executes command in child process
            fprintf(stderr, "command not found: %s\n", tokens[0]);
            free(trimmed_tokens);
            exit(EXIT_FAILURE);
        }
        free(trimmed_tokens);
    } else if (pid < 0) {  // Child process was not created
        fprintf(stderr, "cannot create child process\n");
        exit(EXIT_FAILURE);
    } else { // parent process
        waitpid(pid, &pid_status, 0);
    }
}
