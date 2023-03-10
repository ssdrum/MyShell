#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>
#include "myshell.h"


/*
 * char *filename: name of the file to open
 * int append: flag that triggers append mode
 * redirects stdout to the file specified by filename. If append is 0,
 * redirects in write mode. If append is 1, redirects in append mode.
 */
int redirect_stdout(char *filename, int append) {
    int fd = open(filename, O_CREAT | O_WRONLY | (append ? O_APPEND : 0), 0666); // Tries to open file filename
    if (fd < 0) {
        fprintf(stdout, "cannot open file: %s", filename);
    }
    int new_out = dup(1); // Allocates new file descriptor that refers to new stdout
    dup2(fd, 1); // Reassigns stdout to fd
    close(fd);
    return new_out;
}


/*
 * int saved_stdout: file descriptor for new stdout
 * Restores stdout
 */
void restore_stdout(int saved_stdout) {
    dup2(saved_stdout, 1);
    close(saved_stdout);
}


/*
 * (*command)(char**): pointer to an internal command function
 * char **tokens: array of tokens
 * Redirects stdout if > or >> is in tokens. Calls the function passed as
 * command. Lastly, restores stdout to default stream.
 */
void handle_intern_cmd(void (*command)(char**), char **tokens) {
    char **trimmed_tokens;
    int saved_stdout;

    int i;
    for (i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], ">") == 0) {
            trimmed_tokens = trim_arr(tokens, i - 1); // Removes all tokens after and including >
            saved_stdout = redirect_stdout(tokens[i + 1], 0); // Redirects stdout in write mode
            (*command)(trimmed_tokens); // Executes command
            restore_stdout(saved_stdout); // Restores stdout
            free(trimmed_tokens);
            return;
        } else if (strcmp(tokens[i], ">>") == 0) {
            trimmed_tokens = trim_arr(tokens, i - 1); // Removes all tokens after and including >>
            saved_stdout = redirect_stdout(tokens[i + 1], 1); // Redirects stdout in append mode
            (*command)(trimmed_tokens); // Executes command
            restore_stdout(saved_stdout); // Restores stdout
            free(trimmed_tokens);
            return;
        }
    }

    (*command)(tokens); // No output redirection
}


/*
 * char **tokens: array of tokens
 * Changes directory. Sets environment variable PWD accordingly.
 */
void cd_in(char **args) {
    char cwd[MAX_BUFFER], nwd[MAX_BUFFER]; // Current and new working directory
    int is_changed;
    int num_tokens;

    num_tokens = array_len(args);
    if (num_tokens == 2) { // path was entered as argument
        strncpy(nwd, args[1], MAX_BUFFER); // Copies path passed as argument to nwd
        is_changed = chdir(nwd);
        if (is_changed == 0) { // chdir returns 0 if no error occurred
            getcwd(cwd, sizeof(cwd)); // Changes directory to the path in cwd
            setenv("PWD", cwd, 1); // Sets PWD environment variable to cwd
        } else {
            fputs("path does not exist\n", stdout); // Invalid path entered
        }
    } else if (num_tokens > 2) {
        fputs("cd: too many arguments\n", stdout); // Too many arguments passed to cd
    }
}


/*
 * Prints all environmental variables
 */
void environ_in() {
    extern char **environ;
    int i = 0;
    while (environ[i] != NULL) {
        fprintf(stdout, "%s\n", environ[i++]);
    }
}


/*
 * char **tokens: array of tokens
 * Implementation of echo commmand. Substitutes multiple spaces or tabs with a single space.
 */
void echo_in(char **tokens) {
    int i = 1;
    while (tokens[i] != NULL) {
        fprintf(stdout, "%s ", tokens[i++]);
    }
    fprintf(stdout, "\n");
}


/*
 * Pauses shell until enter is pressed
 */
void pause_in() {
    char c;
    while(c != '\n') {
        c = fgetc(stdin);
    }
}


/*
 * Just calls ls -al
 */
void dir_in() {
    system("ls -al");
}


/*
 * Just calls clear
 */
void clr_in() {
    system("clear");
}
