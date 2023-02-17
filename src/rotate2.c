/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:19:24 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 15:19:50 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// brings bottom element of A to top
void	rra(t_struct **stack_a)
{
	rev_rotate(stack_a);
	ft_putstr("rra\n");
}

// brings bottom element of B to top
void	rrb(t_struct **stack_b)
{
	rev_rotate(stack_b);
	ft_putstr("rrb\n");
}

// brings bottom element of A and B to top
void	rrr(t_struct **stack_a, t_struct **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	ft_putstr("rrr\n");
}