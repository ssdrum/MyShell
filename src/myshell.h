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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BUFFER 2048
#define MAX_ARGS 64
#define PROMPT "$"

// Internal commands arrays
extern char *internal_commands[];
extern void (*internal_function[])(char **args);

// Internal commands handler
void handle_intern_cmd(void (*command)(char**), char **tokens);

// Utils
int array_len(char **arr);
int get_last_arg(char **args);
char **trim_arr(char **arr, int end);
char **split(char *str, char *delim);

// Fork/exec handling
void handle_ext_cmd(char **tokens, int background_mode);
