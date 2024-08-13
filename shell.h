#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int shell_execute(char **args);
void prompt_main(char **input_line);
int dash_exit(void);
#endif
