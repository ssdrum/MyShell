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
            - dir writes a list of all directories and files in the current working directory to the standard output, along with information 
              about permissions and last modification. 
            - environ writes a list of all environment variables to the standard output.
            - echo [string ...] writes string to the standard output. Substitutes all tabs and spaces with a single space.
            - pause pauses the shell until the user presses enter.
            - help displays this manual using the more system program.
            - quit stops execution of the shell.

## I/O REDIRECTION
        Myshell is capable of input and output redirection, meaning that it can read and write from files specified by the user (default is stdin 
        and stdout). 
        The options are:
            - program > outfile:  The output of "program" is redirected to "outfile" in write mode.
            - program >> outfile: The output of "program" is redirected to "outfile" in append mode.
            - program < infile:   "program" will take input from "infile".

## PROGRAM ENVIRONMENT
        Unix-based operating systems come with a set of environment variables. These environment variables can affect how a program behaves.
        In practice, environment variables are simply key-value pairs, and can be accessed by processes such as this shell.
        Examples of common environment variables are:
            - HOME absolute path to the home directory.
            - SHELL absolute path to the shell executable.
            - PWD absolute path to the current working directory. 
        There are many more environment variable available, and they can be seen in this shell by using the environ command.

## BACKGROUND AND FOREGROUND PROCESSES
        If a user executes an external program in this shell, a new process is created and assigned to it. The program runs in the foreground by
        default. However, if the command is appended with a &, then the program is run in the background.
        A program that runs in the foreground is a program that requires the user to interact with it.
        A program that runs in the background is a program that does not require the user to interact with it.

## REFERENCES
www.ibm.com. (n.d.). Processes. [online] Available at: https://www.ibm.com/docs/en/aix/7.2?topic=processes- [Accessed 11 Mar. 2023].
www.ibm.com. (n.d.). Environment variables. [online] Available at: https://www.ibm.com/docs/en/sdk-java-technology/8?topic=reference-environment-variables [Accessed 11 Mar. 2023].
linux.die.net. (n.d.). Linux man pages. [online] Available at: https://linux.die.net/man/ [Accessed 11 Mar. 2023].
Brennan, S. (2015). Tutorial - Write a Shell in C - Stephen Brennan. [online] Stephen Brennan’s Blog. Available at: https://brennan.io/2015/01/16/write-a-shell-in-c/ [Accessed 11 Mar. 2023].




Author: Luigi Di Paolo
Student number: 21725939

I understand that the University regards breaches of academic integrity and
plagiarism as grave and serious.
I have read and understood the DCU Academic Integrity and Plagiarism Policy.
I accept the penalties that may be imposed should I engage in practice or
practices that breach this policy.
I have identified and included the source of all facts, ideas, opinions and 
viewpoints of others in the assignment references. Direct quotations, 
paraphrasing, discussion of ideas from books, journal articles, internet 
sources, module text, or any other source whatsoever are acknowledged and 
the sources cited are identified in the assignment references.
I declare that this material, which I now submit for assessment, is entirely
my own work and has not been taken from the work of others save and to the 
extent that such work has been cited and acknowledged within the text of my
work.
I have used the DCU library referencing guidelines and/or the appropriate 
referencing system recommended in the assignment guidelines and/or programme
documentation. 
