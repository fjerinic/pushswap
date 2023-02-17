/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:26:52 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:19:00 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_target(t_struct **a, int b_idx,
								int target_idx, int t_position)
{
	t_struct	*tmp_a;

	tmp_a = *a;
	while (tmp_a)
	{
		if (tmp_a->index > b_idx && tmp_a->index < target_idx)
		{
			target_idx = tmp_a->index;
			t_position = tmp_a->position;
		}
		tmp_a = tmp_a->next;
	}
	if (target_idx != INT_MAX)
		return (t_position);
	tmp_a = *a;
	while (tmp_a)
	{
		if (tmp_a->index < target_idx)
		{
			target_idx = tmp_a->index;
			t_position = tmp_a->position;
		}
		tmp_a = tmp_a->next;
	}
	return (t_position);
}

void	get_target_position(t_struct **a, t_struct **b)
{
	t_struct	*tmp_b;
	int			t_position;

	tmp_b = *b;
	get_position(a);
	get_position(b);
	t_position = 0;
	while (tmp_b)
	{
		t_position = get_target(a, tmp_b->index, INT_MAX, t_position);
		tmp_b->t_position = t_position;
		tmp_b = tmp_b->next;
	}
}

int	get_min_index_pos(t_struct **stack)
{
	t_struct	*tmp;
	int			lowest_index;
	int			lowest_pos;

	tmp = *stack;
	lowest_index = INT_MAX;
	get_position(stack);
	lowest_pos = tmp->position;
	while (tmp)
	{
		if (tmp->index < lowest_index)
		{
			lowest_index = tmp->index;
			lowest_pos = tmp->position;
		}
		tmp = tmp->next;
	}
	return (lowest_pos);
}

void	get_position(t_struct **stack)
{
	t_struct	*tmp;
	int			n;

	tmp = *stack;
	n = 0;
	while (tmp)
	{
		tmp->position = n;
		tmp = tmp->next;
		n++;
	}
}

// push all elements from stack a to stack b except the 3 last ones
// first pushes smallest and then largest
void	push_all_save_three(t_struct **stack_a, t_struct **stack_b)
{
	int	stack_size;
	int	pushed;
	int	n;

	stack_size = fn_stack_size(*stack_a);
	pushed = 0;
	n = 0;
	while (stack_size > 6 && n < stack_size && pushed < stack_size / 2)
	{
		if ((*stack_a)->index <= stack_size / 2)
		{
			pb(stack_a, stack_b);
			pushed++;
		}
		else
			ra(stack_a);
		n++;
	}
	while (stack_size - pushed > 3)
	{
		pb(stack_a, stack_b);
		pushed++;
	}
}
