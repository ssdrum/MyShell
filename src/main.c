#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "my-shell.h"


// Prototypes
void run_shell();

// Constants
char *PROMPT = "$ ";
char *DELIM = " \t"; // Use spaces and tabs as delimeters


int main(int argc, char *argv[]) {
    run_shell();
    return 0;
}


void run_shell() {
    char buf[MAX_BUFFER]; // 1024
    char **tokens;
    int num_tokens;

    while(1) {
        fputs(PROMPT, stdout); // Prints prompt
        if (fgets(buf, MAX_BUFFER, stdin)) { // Takes input
            buf[strcspn(buf, "\n")] = 0; // Removes trailing newline
            tokens = split(buf, DELIM); // Stores tokens in NULL-terminated array
            num_tokens = array_len(tokens);

             // Internal commands
            if (tokens[0] != NULL) { // Checks for empty input line
                if (strcmp(tokens[0], "clr") == 0) {
                    system("clear");
                } else if (strcmp(tokens[0], "dir") == 0)  {
                    system("ls -al");
                } else if (strcmp(tokens[0], "cd") == 0)  {
                    change_dir(tokens, num_tokens);
                } else if (strcmp(tokens[0], "quit") == 0) {
                    exit(0);
                }
            }
        }
    }
}
