#include "monty.h"

FILE *file_s;
char *line_buf;

/**
 * op_swap - swaps the top two elements of the stack; failure if
 * < 2 elements in stack
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_swap(stack_t **stack, unsigned int line_number)
{
	int temp_n;

	if (*stack && (*stack)->next)
	{
		temp_n = (*stack)->n;
		(*stack)->n = (*stack)->next->n;
		(*stack)->next->n = temp_n;
	}
	else
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_add - finds sum of top two elements in the stack; failure if
 * < 2 elements in stack
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int sum;

	if (*stack && (*stack)->next)
	{
		sum = (*stack)->n + (*stack)->next->n;
		(*stack)->next->n = sum;
		*stack = (*stack)->next;
		free(temp);
		printf("t:add: stack at: %p, value: %i\n", (void *)*stack, (*stack)->n);
	}
	else
	{
		fprintf(stderr, "L%u: can't add, stack too short\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_nop - "no operation," line skipped
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
