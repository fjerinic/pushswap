/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:18:23 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 15:18:34 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// top element sent to bottom
void	rotate(t_struct **stack)
{
	t_struct	*tmp;
	t_struct	*tail;

	tmp = *stack;
	*stack = (*stack)->next;
	tail = stack_bottom(*stack);
	tmp->next = NULL;
	tail->next = tmp;
}

// sends top element of A to bottom
void	ra(t_struct **stack_a)
{
	rotate(stack_a);
	ft_putstr("ra\n");
}

// sends top element of B to bottom
void	rb(t_struct **stack_b)
{
	rotate(stack_b);
	ft_putstr("rb\n");
}

// sends top element of A and B to bottom
void	rr(t_struct **stack_a, t_struct **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	ft_putstr("rr\n");
}

// brings the bottom element to the top
void	rev_rotate(t_struct **stack)
{
	t_struct	*tmp;
	t_struct	*tail;
	t_struct	*before_tail;

	tail = stack_bottom(*stack);
	before_tail = stack_before_bottom(*stack);
	tmp = *stack;
	*stack = tail;
	(*stack)->next = tmp;
	before_tail->next = NULL;
}