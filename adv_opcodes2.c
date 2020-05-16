#include "monty.h"

/**
 * op_pchar - prints the int at top of stack as char, followed by a new line;
 * failure if int is not a printable ASCII value, or stack is empty
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack)
	{
		if ((*stack)->n >= ' ' && (*stack)->n <= '~')
/*		    || (*stack)->n == '\n') */
		{
			printf("%c\n", (*stack)->n);
		}
		else
		{
			fprintf(stderr, "L%u: can't pchar, value out of range\n",
				line_number);
			cleanup(stack);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_pstr - prints the int values in the stack, starting at the top, as chars,
 * followed by a new line; ends if stack is empty, or when int is not a
 * printable ASCII value
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;

	while (temp)
	{
		if (temp->n == '\0')
			break;
/*		    || temp->n == '\n') */
		if (temp->n >= ' ' && temp->n <= '~')
			putchar(temp->n);
		else
			break;
		temp = temp->next;
	}
	putchar('\n');
}

/**
 * op_rotl - rotates top element of stack to bottom of stack, 2nd becomes top
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *tail, *temp;

	(void)line_number;

	if (*stack && (*stack)->next)
	{
		tail = *stack;
		*stack = (*stack)->next;
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		temp->next = tail;
		tail->prev = temp;
		tail->next = NULL;
	}
}

/**
 * op_rotr - rotates bottom element of stack to top of stack
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void)line_number;

	if (*stack && (*stack)->next)
	{
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		temp->prev->next = NULL;
		(*stack)->prev = temp;
		temp->prev = NULL;
		temp->next = *stack;
		*stack = temp;
	}
}
