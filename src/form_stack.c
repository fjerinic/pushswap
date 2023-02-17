/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:15:05 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:14:04 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// returns second to last element
t_struct	*stack_before_bottom(t_struct *stack)
{
	while (stack && stack->next && stack->next->next != NULL)
		stack = stack->next;
	return (stack);
}

// creates new stack element and returns it
t_struct	*stack_new(int value)
{
	t_struct	*new;

	new = malloc(sizeof * new);
	if (!new)
		return (NULL);
	new->value = value;
	new->index = 0;
	new->position = -1;
	new->t_position = -1;
	new->cost_a = -1;
	new->cost_b = -1;
	new->next = NULL;
	return (new);
}

// adds element to the bottom of a stack
void	stack_add_bottom(t_struct **stack, t_struct *new)
{
	t_struct	*tail;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	tail = stack_bottom(*stack);
	tail->next = new;
}

// returns the number of elements in a stack
int	fn_stack_size(t_struct	*stack)
{
	int	size;

	size = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}

// fills stack a with values from command line arguments
t_struct	*fill_stack(int argc, char **argv)
{
	t_struct	*stack_a;
	long int	number;
	int			n;

	stack_a = NULL;
	number = 0;
	n = 1;
	while (n < argc)
	{
		number = ft_atoi(argv[n]);
		if (number > INT_MAX || number < INT_MIN)
			exit_error(&stack_a, NULL);
		if (n == 1)
			stack_a = stack_new((int)number);
		else
			stack_add_bottom(&stack_a, stack_new((int)number));
		n++;
	}
	return (stack_a);
}
