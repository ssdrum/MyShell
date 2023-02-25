#define MAX_BUFFER 1024
#define MAX_ARGS 3

char **split(char *str, char *delim);
void change_dir(char **args, int num_tokens);
int array_len(char **arr);
