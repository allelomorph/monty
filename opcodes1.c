#include "monty.h"

FILE *file_s;
char *line_buf;

/**
 * op_push - pushes an element to the stack; failure if second token from
 * iterpreter is not an int value
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_push(stack_t **stack, unsigned int line_number)
{
	char *push_n = NULL;
	long int value = 0;
	stack_t *TOS = NULL;

	push_n = strtok(NULL, " ");
	if (!push_n)
	{
		fprintf(stderr, "L%u: usage: push integer\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
	value = strtol(push_n, NULL, 10);
	if (!value)
	{
		if (push_n[0] != '0') /* user didn't enter '0', strtol error */
		{
			fprintf(stderr, "L%u: usage: push integer\n",
				line_number);
			cleanup(stack);
			exit(EXIT_FAILURE);
		}
	}
	TOS = malloc(sizeof(stack_t));
	if (!TOS)
	{
		fprintf(stderr, "Error: malloc failed\n");
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (*stack)
			(*stack)->prev = TOS;
		TOS->n = value;
		TOS->prev = NULL;
		TOS->next = *stack;
		*stack = TOS;
	}
}

/**
 * op_pall - prints all int values in the stack, top to bottom, each followed
 * by a newline
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;

	while (temp)
	{
		printf("%i\n", temp->n);
		temp = temp->next;
	}
}

/**
 * op_pint - prints int value at top of stack; failure if stack is empty
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_pint(stack_t **stack, unsigned int line_number)
{
	if (*stack)
	{
		printf("%i\n", (*stack)->n);
	}
	else
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_pop - removes top element of stack, if stack > 1 elements, second element
 * becomes top of stack; failure if stack is empty
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (*stack)
	{
		if ((*stack)->next)
		{
			*stack = (*stack)->next;
			(*stack)->prev = NULL;
			free(temp);
		}
		else
		{
			free(*stack);
			*stack = NULL;
		}
	}
	else
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}
