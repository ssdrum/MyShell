#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "myshell.h"


// Constants
char *DELIM = " \t"; // Use spaces and tabs as delimeters


// Prototypes
void run_shell(FILE *batch_file);
FILE *set_input_stream(FILE *batch_file);


/*
 * Main function. Calls run_shell passing the batch file to it as argument
 */
int main(int argc, char *argv[]) {
    FILE *batch_file = NULL;

    if (argc == 2) {
        batch_file = fopen(argv[1], "r");
        // Batch file does not exist
        if (batch_file == NULL) {
            fprintf(stdout, "cannot open %s\n", argv[1]);
            exit(EXIT_FAILURE);
        } 
    }
    run_shell(batch_file);
    return 0;
}


/*
 * FILE *batch_file: File pointer to a batch file
 * Assigns environment variables, takes input, handles internals and external
 * commands.
 */
void run_shell(FILE *batch_file) {
    char buf[MAX_BUFFER], cwd[MAX_BUFFER];
    char **tokens;
    int background_mode, num_internal_commands;
    FILE *input_stream;

    signal(SIGINT, handle_sigint);

    // Input stream is stdin if batchfile is not provided, otherwise is batchfile
    num_internal_commands = array_len(internal_commands);
    input_stream = set_input_stream(batch_file);

    // Assigns absolute path of current working directory to cwd
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/myshell");
    setenv("SHELL", cwd, 1);

    // Main loop that takes input
    while(!feof(input_stream)) {
        // 0 for false, 1 for true. Default is false
        background_mode = 0;
        getcwd(cwd, sizeof(cwd)); 

        // Prints current working directory and prompt
        if (batch_file == NULL) {
            fprintf(stdout, "%s %s ", cwd, PROMPT);
        }

        // Takes input
        if (fgets(buf, MAX_BUFFER, input_stream)) {
            // Prints input if coming from a batch file
            if (batch_file != NULL) {
                fputs(buf, stdout);
            }

            // Removes trailing newline
            buf[strcspn(buf, "\n")] = 0;
            // Stores tokens in NULL-terminated array
            tokens = split(buf, DELIM);

            // Internal commands
            if (tokens[0] != NULL) {
                // Flips backgroud execution flag if last token is &
                if (strcmp(tokens[array_len(tokens) - 1], "&") == 0) {
                    background_mode = 1;
                }

                // Check if command is an internal command
                int i = 0;
                while (i < num_internal_commands &&
                       strcmp(tokens[0], internal_commands[i]) != 0) {
                    i++;
                }

                // Executes command
                if (i == num_internal_commands) {
                    handle_ext_cmd(tokens, background_mode);
                } else {
                    handle_intern_cmd(internal_function[i], tokens);
                }
            }
            free(tokens);
        }
    }
}


/*
 * FILE *batch_file: File pointer to a batch file
 * Assigns input stream. If no batch file is provided, assigns input stream to
 * stdin.
 */
FILE *set_input_stream(FILE *batch_file) {
    FILE *input_stream;

    if (batch_file == NULL) {
        input_stream = stdin;
    } else {
        input_stream = batch_file;
    }
    return input_stream;
}


/*
 * Signal interrupt handler
 */
void handle_sigint(int sig) {
    run_shell(NULL);
}
