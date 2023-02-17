/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:23:32 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 15:23:42 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	arg_is_number(char *argv)
{
	int	n;

	n = 0;
	if (is_sign(argv[n]) && argv[n + 1] != '\0')
		n++;
	while (argv[n] && is_digit(argv[n]))
		n++;
	if (argv[n] != '\0' && !is_digit(argv[n]))
		return (0);
	return (1);
}

int	is_duplicate(char **argv)
{
	int	n;
	int	j;

	n = 1;
	while (argv[n])
	{
		j = 1;
		while (argv[j])
		{
			if (j != n && nbstr_cmp(argv[n], argv[j]) == 0)
				return (1);
			j++;
		}
		n++;
	}
	return (0);
}

int	arg_is_zero(char *argv)
{
	int	n;

	n = 0;
	if (is_sign(argv[n]))
		n++;
	while (argv[n] && argv[n] == '0')
		n++;
	if (argv[n] != '\0')
		return (0);
	return (1);
}

int	check_input(char **argv)
{
	int	n;
	int	nb_zeros;

	nb_zeros = 0;
	n = 1;
	while (argv[n])
	{
		if (!arg_is_number(argv[n]))
			return (0);
		nb_zeros += arg_is_zero(argv[n]);
		n++;
	}
	if (nb_zeros > 1)
		return (0);
	if (is_duplicate(argv))
		return (0);
	return (1);
}