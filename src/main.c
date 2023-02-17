/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:39:46 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:27:46 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_struct	*stack_a;
	t_struct	*stack_b;
	int			stack_size;

	if (argc < 2)
		return (0);
	if (!check_input(argv))
		exit_error(NULL, NULL);
	stack_b = NULL;
	stack_a = fill_stack(argc, argv);
	stack_size = fn_stack_size(stack_a);
	indexation(stack_a, stack_size + 1);
	push_swap(&stack_a, &stack_b, stack_size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

//chooses a sorting method depending on the size of the stack
void	push_swap(t_struct **stack_a, t_struct **stack_b, int stack_size)
{
	if (stack_size == 2 && !check_sorted(*stack_a))
		sa(stack_a);
	else if (stack_size == 3)
		sort_three(stack_a);
	else if (stack_size > 3 && !check_sorted(*stack_a))
		sort(stack_a, stack_b);
}

// checks if stack is sorted
int	check_sorted(t_struct *stack)
{
	while (stack->next != NULL)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

//frees each element in a stack, nulls the pointer
void	free_stack(t_struct **stack)
{
	t_struct	*tmp;

	if (!stack || !(*stack))
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

// frees stacks and exits with error code 1
void	exit_error(t_struct **stack_a, t_struct **stack_b)
{
	if (stack_a == NULL || *stack_a != NULL)
		free_stack(stack_a);
	if (stack_b == NULL || *stack_b != NULL)
		free_stack(stack_b);
	write(2, "Error\n", 6);
	exit (1);
}
