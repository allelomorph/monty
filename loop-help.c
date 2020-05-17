#include "monty.h"

/**
 * cleanup - uses global variables FILE *file_s and char *line_buf plus arg
 * stack_t **stack to free allocated memory before any conditional exit().
 * @stack: double pointer to top element in stack
 */
void cleanup(stack_t **stack)
{
	stack_t *temp;

	if (line_buf)
		free(line_buf);
	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
	fclose(file_s);
}

/**
 * opcode_select - checks opcode string against list of opcode names,
 * calling a function if matched
 * @opcode: first ' ' delimited token of input line from parse_loop()
 * @stack: double pointer to top element in stack
 * @line_number: current line of monty file seen by interpreter
 * Return: 0 on success, 1 on failure (no match found)
 */
int opcode_select(char *opcode, stack_t **stack, unsigned int line_number)
{
	int i;
	instruction_t codes[] = {
		{"push", (*op_push)},
		{"pall", (*op_pall)},
		{"pint", (*op_pint)},
		{"pop", (*op_pop)},
		{"swap", (*op_swap)},
		{"add", (*op_add)},
		{"nop", (*op_nop)},
		{"sub", (*op_sub)},
		{"div", (*op_div)},
		{"mul", (*op_mul)},
		{"mod", (*op_mod)},
		{"pchar", (*op_pchar)},
		{"pstr", (*op_pstr)},
		{"rotl", (*op_rotl)},
		{"rotr", (*op_rotr)},
		{"stack", (*op_stack)},
		{"queue", (*op_queue)},
		{NULL, NULL}
	};

	for (i = 0; codes[i].opcode; i++)
	{
		if (!strcmp(opcode, codes[i].opcode))
		{
			codes[i].f(stack, line_number);
			return (0);
		}
	}
	if (!codes[i].opcode)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n",
			line_number, opcode);
		return (1);
	}
	return (0);
}

/**
 * get_line - wrapper for getline() to handle errors and EOF exit
 * @file: file stream currently being parsed by interpreter
 * @stack: single pointer to top element in stack
 * Return: buffer read by getline(), with terminal '\n' replaced with '\0'
 */
char *get_line(FILE *file, stack_t *stack)
{
	size_t buf_bytes = 0;
	ssize_t read_bytes;

	read_bytes = getline(&line_buf, &buf_bytes, file);
	if (read_bytes == -1)
	{
		/* EOF reached */
		if (errno == 0)
		{
			cleanup(&stack);
			exit(EXIT_SUCCESS);
		}
		/* other read failure */
		else
		{
			fprintf(stderr, "t:getline failure\n");
			cleanup(&stack);
			exit(EXIT_FAILURE);
		}
	}
	/* remove newline */
	if (line_buf)
		line_buf[read_bytes - 1] = '\0';
	return (line_buf);
}

/**
 * parse_loop - main loop of monty file interpreter, reads file stream line
 * by line, converting text strings into mainpulations of a doubly linked
 * list of ints
 * @file: file stream currently being parsed by interpreter
 */
void parse_loop(FILE *file)
{
	char *line = NULL, *uncomment = NULL, *opcode = NULL;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	is_queue = 0;
	do {
		line_number++;
		line = get_line(file, stack);
		if (line[0] == '#')
		{
			free(line_buf);
			continue;
		}
		else
			uncomment = strtok(line, "#");
		opcode = strtok(uncomment, " ");
		if (line[0] == '\0' || !opcode)
		{
			free(line_buf);
			continue;
		}
		if (opcode_select(opcode, &stack, line_number) == 1)
			break;
		free(line_buf);
	} while (line);
	cleanup(&stack);
	exit(EXIT_FAILURE);
}
