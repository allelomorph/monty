#include "monty.h"

FILE *file_s;

/**
 * main - entry point for "monty," a .m file interpreter
 * @argc: number of command line arguments
 * @argv: array of strings containing command line arguments
 * Return: 0 on success. all failure cases handled with exit()
 * directly from functions.
 */
int main(int argc, char **argv)
{
	file_s = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_s = fopen(argv[1], "r");
	if (!file_s)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	parse_loop(file_s);
	return (0);
}
