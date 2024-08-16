#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int shell_execute(char **args);
void prompt_main(char **input_line);
int dash_exit(void);
char *read_line();
char **split_token(char *input_line);
char *shell_path(char *filename);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
#endif
