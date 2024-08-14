#include "shell.h"
/**
 * prompt_main - Displays a prompt and reads input from the user.
 * @input_line: Pointer to a string where the input line will be stored.
 *
 * This function enters an infinite loop where it displays a prompt (`$ `),
 * reads a line of input from the user, and prints the input back to the
 * standard output. The input is read using the `getline` function, which
 * dynamically allocates memory for the input buffer. The function handles
 * memory cleanup before exiting the program.
 *
 * Return: This function does not return; it exits the program on completion.
 */
void prompt_main(char **input_line)
{

	while (1)
	{
		printf("$ ");

		*input_line = shell_read_line();

		printf("%s", *input_line);

		free(*input_line);
	}
	exit(EXIT_SUCCESS);


}
