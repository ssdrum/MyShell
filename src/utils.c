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

#include "myshell.h"


/*
 * char *str: string
 * char *delim: string
 * Splits str on the characters specified by DELIM. Returns a NULL terminated
 * array of the substrings.
 */
char **split(char *str, char *delim) {
    // Avoids bus error
    char *cpy = strdup(str);
    char **tokens = calloc(1, sizeof(char*));

    char *token = strtok(cpy, delim);
    // stops if user entered too many tokens
    int i = 0;
    while (token != NULL && i <= MAX_ARGS) {
        tokens[i++] = token;
        tokens = realloc(tokens, (i + 1) * sizeof(char*));
        token = strtok(NULL, delim);
    }
    // Adds NULL as last element of the array
    tokens[i] = NULL;

    if (i > MAX_ARGS) {
        // Too many arguments entered
        fputs("too many arguments\n", stdout);
        tokens = realloc(tokens, 1 * sizeof(char*));
        // Returns NULL array
        tokens[0] = NULL;
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
            strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0 &&
            strcmp(args[i], "&") != 0) { 
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
