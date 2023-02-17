/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:20:48 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 15:20:57 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// push top element of src to top of dest
void	push(t_struct **src, t_struct **dest)
{
	t_struct	*tmp;

	if (*src == NULL)
		return ;
	tmp = (*src)->next;
	(*src)->next = *dest;
	*dest = *src;
	*src = tmp;
}

// pushes top element of A to top of B
void	pa(t_struct **stack_a, t_struct **stack_b)
{
	push(stack_b, stack_a);
	ft_putstr("pa\n");
}

// pushes top element of B to top of A
void	pb(t_struct **stack_a, t_struct **stack_b)
{
	push(stack_a, stack_b);
	ft_putstr("pb\n");
}
