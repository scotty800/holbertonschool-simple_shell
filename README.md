
![images (1)](https://github.com/user-attachments/assets/8406017c-c847-43fd-b88c-d5bc6c3c115f)

# Simple Shell

### Introduction


Welcome to the Simple Shell project! This project is the result of a collaboration between Yannis Ranguin and Scotty Nganda as part of our studies in system programming. Our main objective was to develop a minimalist yet functional shell that replicates some of the core features of a traditional Unix shell.

The shell we created is capable of executing simple commands, managing background processes, handling input and output redirection, and interpreting built-in commands. This project allowed us to enhance our C programming skills while gaining a deeper understanding of fundamental operating system concepts such as process management, signal handling, and interacting with the kernel through system calls..

### List of allowed functions and system calls

- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)
## What have we done exactly ?

- Write a README
- Write a man for your shell.
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository.
- Write a beautiful code that passes the Betty checks
- Write a UNIX command line interpreter.
- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)
- Handle command lines with arguments
- Handle the PATH
- fork must not be called if the command doesn’t exist
- Implement the exit built-in, that exits the shell Usage: exit
- You don’t have to handle any argument to the built-in exit
- Implement the env built-in, that prints the current environment
### Requirements

- Allowed editors: vi, vim, emacs

- Operating System: Ubuntu 20.04 or similar

- Compiler: GCC

- Tools: git for version control

- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

### Usage Example

####  Installation

Step 1: Clone the repo

---
```
https://github.com/scotty800/holbertonschool-simple_shell.git 
```

Step 2: directory to holbertonschool-simple_shell:
```
$ cd holbertonschool-simple_shell
```

## Compilation

The code must be compiled this way:
```
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
#### Run the shell
````
$ ./hsh
````
### Flowchart

A faire
## How to use it

In order to use this shell, in a terminal, first run the program:
`./hsh`

It will then display a simple prompt and wait for commands.

`$`

Exemple 1 :
``` 
ls -a
.  ..  .git  README.md  _strcat.c  _strcmp.c  _strcpy.c  _strdup.c  dash_exit.c  hsh  prompt.c  shell.h  shell_execute.c  shell_main.c  shell_path.c  shell_read_line.c  shell_split_token.c
```

Exemple 2
```
"/bin/ls"
README.md  _strcat.c  _strcmp.c  _strcpy.c  _strdup.c  dash_exit.c  hsh  prompt.c  shell.h  shell_execute.c  shell_main.c  shell_path.c  shell_read_line.c  shell_split_token.c
```


## Description of function

- shell_read_line : function reads a line of input from standard input, dynamically allocating and resizing a buffer to fit the input size

- shell_execute : function runs a command by forking a child process, handling errors, and returns 1 to continue or 0 to exit the shell

- prompt.c : function displays a prompt, reads a line of input, and handles errors from getline

- shell_split_token : function splits an input line into tokens based on delimiters, dynamically resizing the token array as needed, and returns the array.

- shell_path : function finds and returns the executable's full path in the system's PATH or NULL if not found or accessible.

-  dash_exit : function terminates the program with a successful exit status.

A Faire 
### Author 

[Yannis Ranguin](https://github.com/Yannis95200)

[Scotty Ndanga](https://github.com/scotty800)
