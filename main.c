#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

int shell_execute(char **args);

int dash_exit(void) {
	printf("Exiting shell...\n");
	return 0;  // Retourne 0 pour indiquer que le shell doit se terminer
}

int main() {
	char *args[] = { "ls", "-a", NULL };  // Exemple de commande à exécuter
	shell_execute(args);
	return 0;
}
