/*
 * Author: Luigi Di Paolo
 * Student number: 21725939
 *
 * I understand that the University regards breaches of academic integrity and
 * plagiarism as grave and serious.
 * I have read and understood the DCU Academic Integrity and Plagiarism Policy.
 * I accept the penalties that may be imposed should I engage in practice or
 * practices that breach this policy.
 * I have identified and included the source of all facts, ideas, opinions and 
 * viewpoints of others in the assignment references. Direct quotations, 
 * paraphrasing, discussion of ideas from books, journal articles, internet 
 * sources, module text, or any other source whatsoever are acknowledged and 
 * the sources cited are identified in the assignment references.
 * I declare that this material, which I now submit for assessment, is entirely
 * my own work and has not been taken from the work of others save and to the 
 * extent that such work has been cited and acknowledged within the text of my
 * work.
 * I have used the DCU library referencing guidelines and/or the appropriate 
 * referencing system recommended in the assignment guidelines and/or programme
 * documentation. 
 */

#include <sys/signal.h>
#include <sys/wait.h>
#include "myshell.h"

// Keeps track of the pid. Is global so that it can be passed to the signal 
// handler function below
pid_t pid;


/**
 * char **tokens: NULL terminated array of char*
 * Redirects stdin and stdout if necessary
 */
void assign_streams(char **tokens) {
    int i;
    for (i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            if (freopen(tokens[i + 1], "r", stdin) == NULL) {
                // Error
                fprintf(stderr, "no such file or directory: %s\n",
                        tokens[i + 1]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(tokens[i], ">") == 0) {
            if (freopen(tokens[i + 1], "w", stdout) == NULL) {
                // Error
                fprintf(stderr, "cannot open file: %s\n", tokens[i + 1]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(tokens[i], ">>") == 0) {
            if (freopen(tokens[i + 1], "a", stdout) == NULL) {
                // Error
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
 * char **tokens: NULL terminated array of char*
 * int background_mode: Background execution flag - 0 for false, 1 for true
 * Handles forking and execution of non-internal commands. Creates a child
 * process which executes the command passed in tokens[0]. Also, reassigns
 * I/O file descriptors if the user is redirecting them.
 */
void handle_ext_cmd(char **tokens, int background_mode) {
    int pid_status, last_arg;
    char **trimmed_tokens;

    last_arg = get_last_arg(tokens);
    trimmed_tokens = trim_arr(tokens, last_arg);

    // Creates child process
    pid = fork();
    if (pid < 0) {
        // Error
        fprintf(stderr, "cannot create child process\n");
        free(trimmed_tokens);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (background_mode) {
            printf("program running in background... %i\n", getpid());
        }
        // Redirect stdin and/or stdout if required
        assign_streams(tokens);
        // Executes command in child process
        if (execvp(trimmed_tokens[0], trimmed_tokens) == -1) {
            fprintf(stderr, "command not found: %s\n", tokens[0]);
            free(trimmed_tokens);
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        // Wait for child process before resuming execution
        if (!background_mode) { 
            // Removes SIGCHILD Handler if not needed
            signal(SIGCHLD, NULL);
            waitpid(pid, &pid_status, 0);
        } else {
            // Wait for child process to be done to print message
            signal(SIGCHLD, handle_child);
        }
    }
    free(trimmed_tokens);
}
