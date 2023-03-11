#include <stdio.h>


#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define PROMPT "$"


// Internal commands arrays
extern char *internal_commands[];
extern void (*internal_function[])(char **args);

void run_shell(FILE *batch_file);

// Internal commands handler
void handle_intern_cmd(void (*command)(char**), char **tokens);

// Utils
int array_len(char **arr);
int get_last_arg(char **args);
char **trim_arr(char **arr, int end);
char **split(char *str, char *delim);

// Fork/exec handling
void handle_ext_cmd(char **tokens, int bg_mode);

// Signal handlers
void handle_sigint(int sig);
