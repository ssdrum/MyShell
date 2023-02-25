#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my-shell.h"


/*
 * char *str: a string
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
