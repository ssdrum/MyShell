#define MAX_BUFFER 1024
#define MAX_ARGS 64


char **split(char *str, char *delim);
void change_dir(char **args, int num_tokens);
int array_len(char **arr);
void print_environ();
void echo(char **tokens);
void fork_exec(char **tokens, int num_tokens);
int get_last_arg(char **args, int num_tokens);
char **trim_arr(char **arr, int pos);
void assign_streams(char **tokens, int num_tokens);
