/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:30:58 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 15:31:24 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// after most of stack is sorted, shift stack to have smallest element
// on top. If it is in the bottom half, shift it to the top with rra
// otherwise shift it to the top with ra
void	shift_struct(t_struct **stack_a)
{
	int	lowest_pos;
	int	stack_size;

	stack_size = fn_stack_size(*stack_a);
	lowest_pos = get_min_index_pos(stack_a);
	if (lowest_pos > stack_size / 2)
	{
		while (lowest_pos < stack_size)
		{
			rra(stack_a);
			lowest_pos++;
		}
	}
	else
	{
		while (lowest_pos > 0)
		{
			ra(stack_a);
			lowest_pos--;
		}
	}
}

// sorting algorithm for stacks of size lagrer than 3
// push all elements from stack a to stack b except the 3 last ones
// sort 3 numbers in a, calcuates most cost-effective move
// shifts elements until stack A is sorted
void	sort(t_struct **stack_a, t_struct **stack_b)
{
	push_all_save_three(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
	{
		get_target_position(stack_a, stack_b);
		get_cost(stack_a, stack_b);
		cheapest_move(stack_a, stack_b);
	}
	if (!check_sorted(*stack_a))
		shift_struct(stack_a);
}


int	find_highest_index(t_struct *stack)
{
	int		index;

	index = stack->index;
	while (stack)
	{
		if (stack->index > index)
			index = stack->index;
		stack = stack->next;
	}
	return (index);
}

void	sort_three(t_struct **stack)
{
	int		highest;

	if (check_sorted(*stack))
		return ;
	highest = find_highest_index(*stack);
	if ((*stack)->index == highest)
		ra(stack);
	else if ((*stack)->next->index == highest)
		rra(stack);
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}