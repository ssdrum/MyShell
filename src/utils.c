#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myshell.h"


/*
 * char *str: string
 * char *delim: string
 * Splits str on the characters specified by DELIM. Returns a NULL terminated
 * array of the substrings.
 */
char **split(char *str, char *delim) {
    char *cpy = strdup(str); // Avoids bus error
    char **tokens = calloc(1, sizeof(char*));

    char *token = strtok(cpy, delim);
    int i = 0;
    while (token != NULL && i <= MAX_ARGS) { // stops if user entered too many tokens
        tokens[i++] = token;
        tokens = realloc(tokens, (i + 1) * sizeof(char*));
        token = strtok(NULL, delim);
    }
    tokens[i] = NULL; // Adds NULL as last element of the array

    if (i > MAX_ARGS) { // Checks if user entered too many arguments
        fputs("too many arguments\n", stdout);
        tokens = realloc(tokens, 1 * sizeof(char*));
        tokens[0] = NULL; // Returns NULL array
    }
    return tokens;
}


/*
 * arr: NULL terminated array
 * Returns number of elements in arr
 */
int array_len(char **arr) {
    int i = 0;
    while(arr[i] != NULL) {
        i++;
    }
    return i;
}


/**
 * args: array of pointers
 * Returns the index of the last token in args that is not equal to >, < or >>.
 * If no matching token is found, returns the number or tokens in args.
 */
int get_last_arg(char **args) {
    int i = 0;
    while (args[i] != NULL && strcmp(args[i], "<") != 0 && 
            strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0) { 
        i++;
    }
    return i - 1;
}


/**
 * args: array of strings
 * pos: index of args
 * Makes a copy of arr with everything after position pos removed. Adds a NULL
 * pointer as last entry
 */
char **trim_arr(char **arr, int end) {
    char **trimmed_arr = malloc(sizeof(char *) * end + 1);
    
    int i;
    for (i = 0; i <= end; i++) {
        trimmed_arr[i] = arr[i];
    }
    trimmed_arr[i] = NULL;
    return trimmed_arr;
}
