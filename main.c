/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:39:46 by fjerinic          #+#    #+#             */
/*   Updated: 2023/02/11 01:15:41 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_struct	*stack_a;
	t_struct	*stack_b;
	int			stack_size;
	if (argc < 2)
		return (0);
	if (!check_input(argv))
		exit_error(NULL, NULL);
	stack_b = NULL;
	stack_a = fill_stack(argc, argv);
	stack_size = fn_stack_size(stack_a);
	indexation(stack_a, stack_size + 1);
	push_swap(&stack_a, &stack_b, stack_size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

//chooses a sorting method depending on the size of the stack
static void	push_swap(t_struct **stack_a, t_struct **stack_b, int stack_size)
{
	if (stack_size == 2 && !check_sorted(*stack_a))
		do_sa(stack_a);
	else if (stack_size == 3)
		sort_three(stack_a);
	else if (stack_size > 3 && !check_sorted(*stack_a))
		sort(stack_a, stack_b);
}

// checks if stack is sorted
int	check_sorted(t_struct *stack)
{
	while (stack->next != NULL)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

//frees each element in a stack, nulls the pointer
void	free_stack(t_struct **stack)
{
	t_struct	*tmp;

	if (!stack || !(*stack))
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

// frees stacks and exits with error code 1
void	exit_error(t_struct **stack_a, t_struct **stack_b)
{
	if (stack_a == NULL || *stack_a != NULL)
		free_stack(stack_a);
	if (stack_b == NULL || *stack_b != NULL)
		free_stack(stack_b);
	write(2, "Error\n", 6);
	exit (1);
}

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
int	to_absolute(int number)
{
	if (number < 0)
		return (number * -1);
	return (number);
}

// reverse rotates stack a and b until both costs are 0
static void	do_rev_rotate_both(t_struct **a, t_struct **b,
												int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		do_rrr(a, b);
	}
}

// rotates stack a and b until both costs are 0
static void	do_rotate_both(t_struct **a, t_struct **b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		do_rr(a, b);
	}
}

// rotates stack a until its in position, depending on cost
static void	do_rotate_a(t_struct **a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			do_ra(a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			do_rra(a);
			(*cost)++;
		}
	}
}

static void	do_rotate_b(t_struct **b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			do_rb(b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			do_rrb(b);
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
void	do_move(t_struct **a, t_struct **b, int cost_a, int cost_b)
{
	if (cost_a < 0 && cost_b < 0)
		do_rev_rotate_both(a, b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		do_rotate_both(a, b, &cost_a, &cost_b);
	do_rotate_a(a, &cost_a);
	do_rotate_b(b, &cost_b);
	do_pa(a, b);
}

// finds cheapest element in stack b with cheapest cost to move
// moves it to correct position in stack a
void	do_cheapest_move(t_struct **stack_a, t_struct **stack_b)
{
	t_struct	*tmp;
	int		cheapest;
	int		cost_a;
	int		cost_b;

	tmp = *stack_b;
	cheapest = INT_MAX;
	while (tmp)
	{
		if (to_absolute(tmp->cost_a) + to_absolute(tmp->cost_b) < to_absolute(cheapest))
		{
			cheapest = to_absolute(tmp->cost_b) + to_absolute(tmp->cost_a);
			cost_a = tmp->cost_a;
			cost_b = tmp->cost_b;
		}
		tmp = tmp->next;
	}
	do_move(stack_a, stack_b, cost_a, cost_b);
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
	int		size_a;
	int		size_b;

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

// swaps two top elements of stack
static void	swap(t_struct *stack)
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
void	do_sa(t_struct **stack_a)
{
	swap(*stack_a);
	ft_putstr("sa\n");
}
// swaps two top elements of stack b
void	do_sb(t_struct **stack_b)
{
	swap(*stack_b);
	ft_putstr("sb\n");
}

// swaps two top elements of stack a and b
void	do_ss(t_struct **stack_a, t_struct **stack_b)
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

// returns second to last element
t_struct	*stack_before_bottom(t_struct *stack)
{
	while (stack && stack->next && stack->next->next != NULL)
		stack = stack->next;
	return (stack);
}

// creates new stack element and returns it
t_struct	*stack_new(int value)
{
	t_struct	*new;

	new = malloc(sizeof * new);
	if (!new)
		return (NULL);
	new->value = value;
	new->index = 0;
	new->position = -1;
	new->t_position = -1;
	new->cost_a = -1;
	new->cost_b = -1;
	new->next = NULL;
	return (new);
}

// adds element to the bottom of a stack
void	stack_add_bottom(t_struct **stack, t_struct *new)
{
	t_struct	*tail;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	tail = stack_bottom(*stack);
	tail->next = new;
}

// returns the number of elements in a stack
int	fn_stack_size(t_struct	*stack)
{
	int	size;

	size = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}

// fills stack a with values from command line arguments
t_struct	*fill_stack(int argc, char **argv)
{
	t_struct		*stack_a;
	long int	number;
	int			n;

	stack_a = NULL;
	number = 0;
	n = 1;
	while (n < argc)
	{
		number = ft_atoi(argv[n]);
		if (number > INT_MAX || number < INT_MIN)
			exit_error(&stack_a, NULL);
		if (n == 1)
			stack_a = stack_new((int)number);
		else
			stack_add_bottom(&stack_a, stack_new((int)number));
		n++;
	}
	return (stack_a);
}

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


static int	arg_is_number(char *argv)
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

static int	is_duplicate(char **argv)
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

static int	arg_is_zero(char *argv)
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

static int	get_target(t_struct **a, int b_idx,
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
	int		t_position;

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
	int		lowest_index;
	int		lowest_pos;

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

static void	get_position(t_struct **stack)
{
	t_struct	*tmp;
	int		n;

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
static void	push_all_save_three(t_struct **stack_a, t_struct **stack_b)
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
			do_pb(stack_a, stack_b);
			pushed++;
		}
		else
			do_ra(stack_a);
		n++;
	}
	while (stack_size - pushed > 3)
	{
		do_pb(stack_a, stack_b);
		pushed++;
	}
}

// after most of stack is sorted, shift stack to have smallest element
// on top. If it is in the bottom half, shift it to the top with rra
// otherwise shift it to the top with ra
static void	shift_struct(t_struct **stack_a)
{
	int	lowest_pos;
	int	stack_size;

	stack_size = fn_stack_size(*stack_a);
	lowest_pos = get_min_index_pos(stack_a);
	if (lowest_pos > stack_size / 2)
	{
		while (lowest_pos < stack_size)
		{
			do_rra(stack_a);
			lowest_pos++;
		}
	}
	else
	{
		while (lowest_pos > 0)
		{
			do_ra(stack_a);
			lowest_pos--;
		}
	}
}

// sorting algorithm for stacks of size lagrer than 3
// push all elements from stack a to stack b except the 3 last ones
// sort 3 numbers in a, calcuates most cost-effective move
// shifts elements until stack A is sorted
void	sort(t_struct **stack_a, t_struct **stack_b)
{
	push_all_save_three(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
	{
		get_target_position(stack_a, stack_b);
		get_cost(stack_a, stack_b);
		do_cheapest_move(stack_a, stack_b);
	}
	if (!check_sorted(*stack_a))
		shift_struct(stack_a);
}


static int	find_highest_index(t_struct *stack)
{
	int		index;

	index = stack->index;
	while (stack)
	{
		if (stack->index > index)
			index = stack->index;
		stack = stack->next;
	}
	return (index);
}

void	sort_three(t_struct **stack)
{
	int		highest;

	if (check_sorted(*stack))
		return ;
	highest = find_highest_index(*stack);
	if ((*stack)->index == highest)
		do_ra(stack);
	else if ((*stack)->next->index == highest)
		do_rra(stack);
	if ((*stack)->index > (*stack)->next->index)
		do_sa(stack);
}

// top element sent to bottom
static void	rotate(t_struct **stack)
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
void	do_ra(t_struct **stack_a)
{
	rotate(stack_a);
	ft_putstr("ra\n");
}

// sends top element of B to bottom
void	do_rb(t_struct **stack_b)
{
	rotate(stack_b);
	ft_putstr("rb\n");
}

// sends top element of A and B to bottom
void	do_rr(t_struct **stack_a, t_struct **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	ft_putstr("rr\n");
}

// brings the bottom element to the top
static void	rev_rotate(t_struct **stack)
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

// brings bottom element of A to top
void	do_rra(t_struct **stack_a)
{
	rev_rotate(stack_a);
	ft_putstr("rra\n");
}

// brings bottom element of B to top
void	do_rrb(t_struct **stack_b)
{
	rev_rotate(stack_b);
	ft_putstr("rrb\n");
}

// brings bottom element of A and B to top
void	do_rrr(t_struct **stack_a, t_struct **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	ft_putstr("rrr\n");
}

// push top element of src to top of dest
static void	push(t_struct **src, t_struct **dest)
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
void	do_pa(t_struct **stack_a, t_struct **stack_b)
{
	push(stack_b, stack_a);
	ft_putstr("pa\n");
}

// pushes top element of B to top of A
void	do_pb(t_struct **stack_a, t_struct **stack_b)
{
	push(stack_a, stack_b);
	ft_putstr("pb\n");
}
