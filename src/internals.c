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

#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <termios.h>
#include "myshell.h"


/*
 * char *filename: name of the file to open
 * int append: flag that triggers append mode
 * redirects stdout to the file specified by filename. If append is 0,
 * redirects in write mode. If append is 1, redirects in append mode.
 */
int redirect_stdout(char *filename, int append) {
    int fd = open(filename, O_CREAT | O_WRONLY | (append ? O_APPEND : 0), 0666);
    if (fd < 0) {
        // Error
        fprintf(stderr, "cannot open file: %s", filename);
    }
    // Allocates new file descriptor that refers to new stdout
    int new_out = dup(1);
    // Reassigns stdout to fd
    dup2(fd, 1);
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
            // Removes all tokens after and including >
            trimmed_tokens = trim_arr(tokens, i - 1);
            // Redirects stdout in write mode
            saved_stdout = redirect_stdout(tokens[i + 1], 0);
            // Executes command
            (*command)(trimmed_tokens);
            // Restores stdout
            restore_stdout(saved_stdout);
            free(trimmed_tokens);
            return;
        } else if (strcmp(tokens[i], ">>") == 0) {
            trimmed_tokens = trim_arr(tokens, i - 1);
            // Redirects stdout in append mode
            saved_stdout = redirect_stdout(tokens[i + 1], 1);
            (*command)(trimmed_tokens);
            restore_stdout(saved_stdout);
            free(trimmed_tokens);
            return;
        }
    }
    // No output redirection
    (*command)(tokens);
}


/*
 * char **tokens: NULL terminated array of char*
 * Changes directory. Sets environment variable PWD accordingly.
 */
void internal_cd(char **args) {
    char buffer[MAX_BUFFER]; // new working directory
    int is_changed;
    int num_tokens;

    num_tokens = array_len(args);
    // Change cwd to home
    if (num_tokens == 1) {
        strncpy(buffer, getenv("HOME"), MAX_BUFFER);
        chdir(buffer);
        setenv("PWD", buffer, 1);
    // Path was entered as argument
    } else if (num_tokens == 2) {
        // Copies path passed as argument to nwd
        strncpy(buffer, args[1], MAX_BUFFER);
        is_changed = chdir(buffer);
         
        // chdir returns 0 if no error occurred
        if (is_changed == 0) {
            getcwd(buffer, sizeof(buffer));
            setenv("PWD", buffer, 1);
        } else {
            // Invalid path entered
            fprintf(stderr, "path does not exist\n");
        }
    } else {
        // Too many arguments
        fprintf(stderr, "cd: too many arguments\n");
    }
}


/*
 * Prints all environmental variables to the standard output
 */
void internal_environ() {
    extern char **environ;
    int i = 0;
    while (environ[i] != NULL) {
        fprintf(stdout, "%s\n", environ[i++]);
    }
}


/*
 * char **tokens: NULL terminated array of char*
 * Implementation of echo commmand. Substitutes multiple spaces or tabs with a
 * single space.
 */
void internal_echo(char **tokens) {
    int i = 1;
    while (tokens[i] != NULL) {
        fprintf(stdout, "%s ", tokens[i++]);
    }
    fprintf(stdout, "\n");
}


/*
 * Pauses shell until enter is pressed
 */
void internal_pause() {
    struct termios config;

    if(tcgetattr(STDIN_FILENO, &config) < 0) {
        fprintf(stderr, "cannot find termios config\n");
        return;
    }

    fprintf(stdout, "Shell is paused. Press Enter to resume\n");
    // Disables echo of keyboard input
    config.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &config);

    // Takes user input until enter is pressed
    char c;
    while(c != '\n') {
        c = fgetc(stdin);
    }

    // Re-enables echo of keyboard input
    config.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &config);
}


/*
 * Calls ls -al
 */
void internal_dir() {
    system("ls -al");
}


/*
 * Calls clear
 */
void internal_clr() {
    system("clear");
}


/*
 * Opens manual using more
 */
void internal_help() {
    char man_path[MAX_BUFFER];
    char buf[MAX_BUFFER];

    strcpy(man_path, getenv("shell"));

    // Finds length of man_path
    int i = 0;
    while (man_path[i] != '\0') {
        i++;
    }
    // Removes /bin/myshell from man_path
    man_path[i - 11] = '\0';
    // Appends manual path
    strcat(man_path, "/manual/readme.md");

    if (snprintf(buf, sizeof(buf), "more -d %s", man_path) < 0) {
        fprintf(stderr, "error");
        exit(EXIT_FAILURE);
    }
    system(buf);
}


/*
 * Exits shell
 */
void internal_quit() {
    exit(EXIT_SUCCESS);
}


/*
 * Array of all internal commands names
 * Note that the order of internal_commands must match the order in
 * internal_funciton
*/
char *internal_commands[] = {
    "cd",
    "clr",
    "dir",
    "environ",
    "echo",
    "pause",
    "help",
    "quit",
    NULL
};


/*
 * Array of pointers to internal commands functions
 */
void (*internal_function[])(char **args) = {
    &internal_cd,
    &internal_clr,
    &internal_dir,
    &internal_environ,
    &internal_echo,
    &internal_pause,
    &internal_help,
    &internal_quit,
    NULL
};
