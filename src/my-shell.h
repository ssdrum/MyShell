#define MAX_BUFFER 1024
#define MAX_ARGS 64


// Internal commands
void cd_in(char **args);
void environ_in();
void pause_in();
void echo_in(char **tokens);
void assign_out_stream(char **tokens);

// Utils
int array_len(char **arr);
int get_last_arg(char **args);
char **trim_arr(char **arr, int end);
char **split(char *str, char *delim);

// Fork/exec handling
void fork_exec(char **tokens);
void assign_streams(char **tokens);
