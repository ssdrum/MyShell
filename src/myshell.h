#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define PROMPT "$"

// Commands

// Internal commands
void cd_in(char **args);
void environ_in();
void pause_in();
void dir_in();
void clr_in();
void echo_in(char **tokens);
void handle_intern_cmd(void (*f)(char**), char **args);

// Utils
int array_len(char **arr);
int get_last_arg(char **args);
char **trim_arr(char **arr, int end);
char **split(char *str, char *delim);

// Fork/exec handling
void handle_ext_cmd(char **tokens, int bg_mode);
