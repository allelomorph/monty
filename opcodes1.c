#include "monty.h"

/**
 * atoi_filter - checks string to see if it represents a valid integer,
 * --note: atoi accommodates leading zeroes on negative numbers, and trailing
 * non-digit chars, both of which are omitted here.
 * @str: string to be checked for compatibility with atoi
 * Return: 0 on valid input, 1 on failure. exit() call made in calling function
 * op_push()
 */
int atoi_filter(char *str)
{
	int i;

	if (!str || str[0] == '\0')
		return (1);

	for (i = 0; str[i]; i++)
	{
		if (i == 0)
		{
			if (str[i] != '-' &&
			    !(str[i] >= 0 + '0' && str[i] <= 9 + '0'))
			{
				return (1);
			}
		}
		else if (!(str[i] >= 0 + '0' && str[i] <= 9 + '0'))
			return (1);
	}
	return (0);
}

/**
 * op_push - pushes an element to the stack; failure if second token from
 * iterpreter is not an int value
 * @stack: first element of a doubly linked LIFO list of integers
 * @line_number: line of monty text file currently seen by interpreter
 */
void op_push(stack_t **stack, unsigned int line_number)
{
	char *push_n = NULL;
	int value = 0;
	stack_t *TOS = NULL;

	push_n = strtok(NULL, " ");
	if (atoi_filter(push_n))
	{
		fprintf(stderr, "L%u: usage: push integer\n",
			line_number);
		cleanup(stack);
		exit(EXIT_FAILURE);
	}
	value = atoi(push_n);

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
