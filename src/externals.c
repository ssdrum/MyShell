#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "myshell.h"


pid_t pid; // Keeps track of the pid. Is global so that it can be passed to the signal handler functiono below


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
 * int sig: Signal
 * Prints a message to stdout that tells the user which process has finished
 * execution
 */
void handle_child(int sig) {
    fprintf(stdout, " + %i done\n", pid);
}

/*
 * char **tokens: Array strings
 * int bg: Background execution flag
 * Handles forking and execution of non-internal commands. Creates a child
 * process which executes the command passed in tokens[0]. Also, reassigns
 * I/O file descriptors if the user is redirecting them.
 */
void handle_ext_cmd(char **tokens, int bg_mode) {
    int pid_status, last_arg;
    char **trimmed_tokens;

    last_arg = get_last_arg(tokens);
    trimmed_tokens = trim_arr(tokens, last_arg);

    pid = fork(); // Creates child process
    if (pid < 0) {  // Error
        fprintf(stderr, "cannot create child process\n");
        free(trimmed_tokens);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process
        if (bg_mode) {
            printf("program running in background... %i\n", getpid());
        }
        assign_streams(tokens); // Redirect stdin and/or stdout if necessary

        if (execvp(trimmed_tokens[0], trimmed_tokens) == -1) { // Executes command in child process
            fprintf(stderr, "command not found: %s\n", tokens[0]);
            free(trimmed_tokens);
            exit(EXIT_FAILURE);
        }
    } else { // parent process
        if (!bg_mode) { // Wait for child process before resuming execution
            signal(SIGCHLD, NULL); // Removes SIGCHILD Handler if not needed
            waitpid(pid, &pid_status, 0);
        } else {
            printf("bg_mode is %i\n", bg_mode);
            signal(SIGCHLD, handle_child); // Wait for child process to be done to print message
        }
    }

    free(trimmed_tokens);
}
