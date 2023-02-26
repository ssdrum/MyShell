#define MAX_BUFFER 1024
#define MAX_ARGS 64


char **split(char *str, char *delim);
void change_dir(char **args);
int array_len(char **arr);
void print_environ();
void echo(char **tokens);
void fork_exec(char **tokens);
int get_last_arg(char **args);
char **trim_arr(char **arr, int end);
void assign_streams(char **tokens);
void assign_out_stream(char **tokens);
