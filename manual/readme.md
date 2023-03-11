# MANUAL: myshell

## NAME
        myshell

## SYNOPSIS
        myshell [file]

## DESCRIPTION
        Myshell is a UNIX command interpreter that executes commands from the standard input or from a file.

## ARGUMENTS 
        The argument file is assumed to be a text file containing shell commands. Myshell reads, writes to standard output, and executes the commands.

## INVOCATION 
        Myshell starts in interactive mode if no optional file is provided as command-line argument.

## BUILT-IN COMMANDS 
        Myshell comes with a set of built-in commands:
            - cd [path] changes the current directory to the one specified in path.
            - clr clears the screen.
            - dir writes a list of all directories and files in the current working directory to the standard output, along with information about permissions and last modification. 
            - environ writes a list of all environment variables to the standard output.
            - echo [string ...] writes string to the standard output. Substitutes all tabs and spaces with a single space.
            - pause pauses the shell until the user presses enter.
            - help displays this manual using the more system program.
            - quit stops execution of the shell.

## I/O REDIRECTION
        Myshell is capable of input and output redirection, meaning that it can read and write from files specified by the user (default is stdin and stdout). 
        The options are:
            - program > outfile:  The output of "program" is redirected to "outfile" in write mode.
            - program >> outfile: The output of "program" is redirected to "outfile" in append mode.
            - program < infile:   "program" will take input from "infile".

## PROGRAM ENVIRONMENT
  
        
        

