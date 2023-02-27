#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "myshell.h"


// Prototypes
void run_shell();

// Constants
char *PROMPT = " $ ";
char *DELIM = " \t"; // Use spaces and tabs as delimeters


int main(int argc, char *argv[]) {
    run_shell();
    return 0;
}


void run_shell() {
    char buf[MAX_BUFFER], cwd[MAX_BUFFER];
    char **tokens;

    getcwd(cwd, sizeof(cwd)); // Assigns absolute path of current working directory to cwd
    strcat(cwd, "/myshell");
    setenv("SHELL", cwd, 1); // TODO Sets SHELL environment variable to this shell To fix

    while(1) {
        getcwd(cwd, sizeof(cwd)); 
        fputs(cwd, stdout); // Prints cwd
        fputs(PROMPT, stdout); // Prints prompt
        if (fgets(buf, MAX_BUFFER, stdin)) { // Takes input
            buf[strcspn(buf, "\n")] = 0; // Removes trailing newline
            tokens = split(buf, DELIM); // Stores tokens in NULL-terminated array

            // TODOS: pause, help
            // Internal commands
            if (tokens[0] != NULL) { // Checks for empty input line
                if (strcmp(tokens[0], "cd") == 0) {
                    cd_in(tokens);
                } else if (strcmp(tokens[0], "clr") == 0)  {
                    system("clear");
                } else if (strcmp(tokens[0], "dir") == 0)  {
                    handle_out_redirect(dir_in, tokens);
                } else if (strcmp(tokens[0], "environ") == 0) {
                    handle_out_redirect(environ_in, tokens);
                } else if (strcmp(tokens[0], "echo") == 0) {
                    handle_out_redirect(echo_in, tokens);
                } else if (strcmp(tokens[0], "pause") == 0) {
                    pause_in();
                } else if (strcmp(tokens[0], "help") == 0) {
                    printf("TODO\n");
                } else if (strcmp(tokens[0], "quit") == 0) {
                    exit(EXIT_SUCCESS);
                } else {
                    fork_exec(tokens); // Handles external commands creating child processes
                }
            }
            free(tokens);
        }
    }
}
