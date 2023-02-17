/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:13:42 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:17:38 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// swaps two top elements of stack
void	swap(t_struct *stack)
{
	int	tmp;

	if (stack == NULL || stack->next == NULL)
		return ;
	tmp = stack->value;
	stack->value = stack->next->value;
	stack->next->value = tmp;
	tmp = stack->index;
	stack->index = stack->next->index;
	stack->next->index = tmp;
}

// swaps two top elements of stack a
void	sa(t_struct **stack_a)
{
	swap(*stack_a);
	ft_putstr("sa\n");
}

// swaps two top elements of stack b
void	sb(t_struct **stack_b)
{
	swap(*stack_b);
	ft_putstr("sb\n");
}

// swaps two top elements of stack a and b
void	ss(t_struct **stack_a, t_struct **stack_b)
{
	swap(*stack_a);
	swap(*stack_b);
	ft_putstr("ss\n");
}

// returns last element of stack
t_struct	*stack_bottom(t_struct *stack)
{
	while (stack && stack->next != NULL)
		stack = stack->next;
	return (stack);
}
