#include "main.h"

void prompt_main(char **input_line)
{
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while (1)
	{
		printf("$ ");
		getline(&line, &len, stdin);
		printf("%s", line);
	}
	printf("$");

	if (line)
	{
		free(line);
	}
	exit(EXIT_SUCCESS);


}
