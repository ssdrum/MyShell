#include <stdio.h>
#include <unistd.h>
#include "my-shell.h"

/*
 * char **tokens: Array strings
 * int num_tokens: Number of elements in tokens
 * Handles forking and execution of non-internal commands. Creates a child
 * process which executes the command passed in tokens[0].
 */
void fork_exec(char **tokens, int num_tokens) {
    pid_t pid;

    pid = fork(); // Creates child process
    if (pid == 0) {  // Child process's id is 0
        printf("child process PID: %i\n", pid);
    } else {
        printf("parent process PID: %i\n", pid);
    }
}
