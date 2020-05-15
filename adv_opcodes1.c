#include "monty.h"

/**
 * op_sub - subtracts the top element of the stack from the second top
 * element of the stack; failure if < 2 elements in list
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int diff;

	if (*stack && (*stack)->next)
	{
		diff = (*stack)->next->n - (*stack)->n;
		(*stack)->next->n = diff;
		*stack = (*stack)->next;
		free(temp);
	}
	else
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_div - divides the second top element of the stack by the top element
 * of the stack; failure if < 2 elements in stack, or top element is 0
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int quot;

	if (*stack && (*stack)->next)
	{
		if ((*stack)->n == 0)
		{
			fprintf(stderr, "L%u: division by zero\n", line_number);
			cleanup(stack);
			exit(EXIT_FAILURE);
		}
		else
		{
			quot = (*stack)->next->n / (*stack)->n;
			(*stack)->next->n = quot;
			*stack = (*stack)->next;
			free(temp);
		}
	}
	else
	{
		fprintf(stderr, "L%u: can't div, stack too short\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_mul - multiplies the second top element of the stack by the top element
 * of the stack; failure if < 2 elements in stack
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int prod;

	if (*stack && (*stack)->next)
	{
		prod = (*stack)->next->n * (*stack)->n;
		(*stack)->next->n = prod;
		*stack = (*stack)->next;
		free(temp);
	}
	else
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * op_mod - finds modulo of the second top element of the stack divided by the
 * top element; failure if < 2 elements in stack, or top element is 0
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int mod;

	if (*stack && (*stack)->next)
	{
		if ((*stack)->n == 0)
		{
			fprintf(stderr, "L%u: division by zero\n", line_number);
			cleanup(stack);
			exit(EXIT_FAILURE);
		}
		else
		{
			mod = (*stack)->next->n % (*stack)->n;
			(*stack)->next->n = mod;
			*stack = (*stack)->next;
			free(temp);
		}
	}
	else
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
}
