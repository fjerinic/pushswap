/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:20:09 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/17 17:20:25 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				position;
	int				t_position;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_struct;

t_struct		*fill_stack(int argc, char **argv);
void			indexation(t_struct *stack_a, int argc);
int				check_sorted(t_struct *stack);
void			sort_three(t_struct **stack);
void			sort(t_struct **stack_a, t_struct **stack_b);
int				get_min_index_pos(t_struct **stack);
void			get_target_position(t_struct **stack_a, t_struct **stack_b);
void			get_cost(t_struct **stack_a, t_struct **stack_b);
void			cheapest_move(t_struct **stack_a, t_struct **stack_b);
void			move(t_struct **a, t_struct **b, int cost_a, int cost_b);
void			pa(t_struct **stack_a, t_struct **stack_b);
void			pb(t_struct **stack_a, t_struct **stack_b);
void			sa(t_struct **stack_a);
void			sb(t_struct **stack_b);
void			ss(t_struct **stack_a, t_struct **stack_b);
void			ra(t_struct **stack_a);
void			rb(t_struct **stack_b);
void			rr(t_struct **stack_a, t_struct **stack_b);
void			rrr(t_struct **stack_a, t_struct **stack_b);
void			rra(t_struct **stack_a);
void			rrb(t_struct **stack_b);
t_struct		*stack_bottom(t_struct *stack);
t_struct		*stack_before_bottom(t_struct *stack);
t_struct		*stack_new(int value);
void			stack_add_bottom(t_struct **stack, t_struct *new);
int				fn_stack_size(t_struct	*stack);
void			free_stack(t_struct **stack);
long int		ft_atoi(const char *str);
void			ft_putstr(char *str);
int				mkabs(int number);
void			exit_error(t_struct **stack_a, t_struct **stack_b);
int				check_input(char **argv);
int				is_digit(char c);
int				is_sign(char c);
int				nbstr_cmp(const char *s1, const char *s2);
void			push_swap(t_struct **stack_a, t_struct **stack_b, int stack_size);
void			get_position(t_struct **stack);
void			rev_rotate_both(t_struct **a, t_struct **b,
												int *cost_a, int *cost_b);
void			rotate_both(t_struct **a, t_struct **b, int *cost_a, int *cost_b);
void			rev_rotate(t_struct **stack);
void			push_all_save_three(t_struct **stack_a, t_struct **stack_b);


#endif