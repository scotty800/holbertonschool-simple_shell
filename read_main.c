#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

int main() 
{
    char *line = read_line();
    printf("Vous avez entré : %s\n", line);
    free(line);
    return 0;
}
