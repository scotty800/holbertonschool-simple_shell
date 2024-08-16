#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stddef.h>

int shell_execute(char **args);
void prompt_main(char **input_line);
int dash_exit(void);
char *read_line();
char **split_token(char *input_line);
char *shell_path(char *filename);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);

#endif
