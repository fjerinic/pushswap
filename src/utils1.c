/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:07:03 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:19:10 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// converts a string to long int
long int	ft_atoi(const char *str)
{
	long int	number;
	int			isneg;
	int			n;

	number = 0;
	isneg = 1;
	n = 0;
	if (str[n] == '+')
		n++;
	else if (str[n] == '-')
	{
		isneg *= -1;
		n++;
	}
	while (is_digit(str[n]))
	{
		number = (number * 10) + (str[n] - '0');
		n++;
	}
	return (number * isneg);
}

void	ft_putstr(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		write(1, &str[n], 1);
		n++;
	}
}

// returns absolute value of an int
int	mkabs(int number)
{
	if (number < 0)
		return (number * -1);
	return (number);
}

// reverse rotates stack a and b until both costs are 0
void	rev_rotate_both(t_struct **a, t_struct **b,
												int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rrr(a, b);
	}
}

// rotates stack a and b until both costs are 0
void	rotate_both(t_struct **a, t_struct **b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rr(a, b);
	}
}
