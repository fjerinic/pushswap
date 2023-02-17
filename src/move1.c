/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:08:17 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:17:11 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// rotates stack a until its in position, depending on cost
void	rotate_a(t_struct **a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ra(a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rra(a);
			(*cost)++;
		}
	}
}

void	rotate_b(t_struct **b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rb(b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rrb(b);
			(*cost)++;
		}
	}
}

// chooses the cheapest move and executes it
// if both costs are negative, do rev rotate both
// if both costs are positive, do rotate both
// then rotate a and b until costs are 0
// also can be rotated seperately
// then push to top of stack a
void	move(t_struct **a, t_struct **b, int cost_a, int cost_b)
{
	if (cost_a < 0 && cost_b < 0)
		rev_rotate_both(a, b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		rotate_both(a, b, &cost_a, &cost_b);
	rotate_a(a, &cost_a);
	rotate_b(b, &cost_b);
	pa(a, b);
}

// finds cheapest element in stack b with cheapest cost to move
// moves it to correct position in stack a
void	cheapest_move(t_struct **stack_a, t_struct **stack_b)
{
	t_struct	*tmp;
	int			cheapest;
	int			cost_a;
	int			cost_b;

	tmp = *stack_b;
	cheapest = INT_MAX;
	while (tmp)
	{
		if (mkabs(tmp->cost_a) + mkabs(tmp->cost_b) < mkabs(cheapest))
		{
			cheapest = mkabs(tmp->cost_b) + mkabs(tmp->cost_a);
			cost_a = tmp->cost_a;
			cost_b = tmp->cost_b;
		}
		tmp = tmp->next;
	}
	move(stack_a, stack_b, cost_a, cost_b);
}

// calculates the cost of moving an element from stack b to stack a
// with correct position in mind. 
// cost a is the distance to the correct position
// cost b is the distance to the top of stack b
// if its in bottom half of stack, cost is negative
// if its in top half of stack, cost is positive
void	get_cost(t_struct **stack_a, t_struct **stack_b)
{
	t_struct	*tmp_a;
	t_struct	*tmp_b;
	int			size_a;
	int			size_b;

	tmp_a = *stack_a;
	tmp_b = *stack_b;
	size_a = fn_stack_size(tmp_a);
	size_b = fn_stack_size(tmp_b);
	while (tmp_b)
	{
		tmp_b->cost_b = tmp_b->position;
		if (tmp_b->position > size_b / 2)
			tmp_b->cost_b = (size_b - tmp_b->position) * -1;
		tmp_b->cost_a = tmp_b->t_position;
		if (tmp_b->t_position > size_a / 2)
			tmp_b->cost_a = (size_a - tmp_b->t_position) * -1;
		tmp_b = tmp_b->next;
	}
}
