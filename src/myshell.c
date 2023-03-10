#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "myshell.h"


// Constants
char *DELIM = " \t"; // Use spaces and tabs as delimeters


// Prototypes
void run_shell(FILE *batch_file);


int main(int argc, char *argv[]) {
    FILE *batch_file = NULL;

    if (argc == 2) {
        batch_file = fopen(argv[1], "r");
        if (batch_file == NULL) { // Batch file does not exist
            fprintf(stdout, "cannot open %s\n", argv[1]);
        } 
    }

    run_shell(batch_file);

    return 0;
}


void run_shell(FILE *batch_file) {
    char buf[MAX_BUFFER], cwd[MAX_BUFFER];
    char **tokens;
    int bg_mode;

    getcwd(cwd, sizeof(cwd)); // Assigns absolute path of current working directory to cwd
    strcat(cwd, "/myshell");
    setenv("SHELL", cwd, 1); // TODO Sets SHELL environment variable to this shell To fix

    while(!feof(stdin)) {
        getcwd(cwd, sizeof(cwd)); 
        if (batch_file == NULL) {
            fprintf(stdout, "%s ", cwd); // Prints current working directory
            fprintf(stdout, "%s ", PROMPT); // Prints prompt
        }
        bg_mode = 0;

        if (fgets(buf, MAX_BUFFER, batch_file == NULL ? stdin : batch_file)) { // Takes input
            buf[strcspn(buf, "\n")] = 0; // Removes trailing newline
            tokens = split(buf, DELIM); // Stores tokens in NULL-terminated array

            // TODOS: help
            // Internal commands
            if (tokens[0] != NULL) { // Checks for empty input line
                                     //
                if (strcmp(tokens[array_len(tokens) - 1], "&") == 0) { // Flips backgroud execution flag if last token is &
                    bg_mode = 1;
                }

                if (strcmp(tokens[0], "cd") == 0) {
                    handle_intern_cmd(cd_in, tokens);
                } else if (strcmp(tokens[0], "clr") == 0)  {
                    handle_intern_cmd(clr_in, tokens);
                } else if (strcmp(tokens[0], "dir") == 0)  {
                    handle_intern_cmd(dir_in, tokens);
                } else if (strcmp(tokens[0], "environ") == 0) {
                    handle_intern_cmd(environ_in, tokens);
                } else if (strcmp(tokens[0], "echo") == 0) {
                    handle_intern_cmd(echo_in, tokens);
                } else if (strcmp(tokens[0], "pause") == 0) {
                    handle_intern_cmd(pause_in, tokens);
                } else if (strcmp(tokens[0], "help") == 0) {
                    printf("TODO\n");
                } else if (strcmp(tokens[0], "quit") == 0) {
                    exit(EXIT_SUCCESS);
                } else {
                    handle_ext_cmd(tokens, bg_mode); // Handles external commands creating child processes
                }
            }
            free(tokens);
        }
    }
}
