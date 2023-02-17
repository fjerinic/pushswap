/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:25:14 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 15:25:23 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// assigns index to each element of stack a. 
// the indexes will be compared instead of the actual values
// higher index means higher value
void	indexation(t_struct *stack_a, int stack_size)
{
	t_struct	*ptr;
	t_struct	*highest;
	int		value;

	while (--stack_size > 0)
	{
		ptr = stack_a;
		value = INT_MIN;
		highest = NULL;
		while (ptr)
		{
			if (ptr->value == INT_MIN && ptr->index == 0)
				ptr->index = 1;
			if (ptr->value > value && ptr->index == 0)
			{
				value = ptr->value;
				highest = ptr;
				ptr = stack_a;
			}
			else
				ptr = ptr->next;
		}
		if (highest != NULL)
			highest->index = stack_size;
	}
}

// compares two strings of numbers and returns 0 if they match
int	nbstr_cmp(const char *s1, const char *s2)
{
	int	n;
	int	j;

	n = 0;
	j = n;
	if (s1[n] == '+')
	{
		if (s2[j] != '+')
			n++;
	}
	else
	{
		if (s2[j] == '+')
			j++;
	}
	while (s1[n] != '\0' && s2[j] != '\0' && s1[n] == s2[j])
	{
		n++;
		j++;
	}
	return ((unsigned char)s1[n] - (unsigned char)s2[j]);
}

// returns 1 if char is a sign
int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

// returns 1 if char is a digit
int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}