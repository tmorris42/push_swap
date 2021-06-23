#include "push_swap.h"
#include <stdio.h> //debug only

int	quicksort_right(t_stack **a, t_stack **b, int amount)
{
	unsigned int	amt_moved;

	amt_moved = 0;
	if (amount == 0 || !stack_len(*b))
		return (0);
	if (amount > -4 && amount < 4)
		put_top_3(a, b, amount);
	else
	{
		if (amount > 0)
			amt_moved = take_highest_x(a, b, ft_abs(amount));
		else
			amt_moved = take_highest_x_rev(a, b, ft_abs(amount));
		quicksort_left(a, b, (int)amt_moved);
		if (amount < 0)
			quicksort_right(a, b, (int)(ft_abs(amount) - amt_moved));
		else
			quicksort_right(a, b, (-1) * (int)(amount - amt_moved));
	}
	return (amt_moved);
}

int	quicksort_left_finish(t_stack **a, t_stack **b, int amount)
{
	if (amount > -4 && amount < 4)
	{
		if (stack_len(*a) < 4)
		{
			sort_3(a, b);
			rotate_high_to_bottom(a);
		}
		else
			sort_top_3(a, b, amount);
	}
	else if (amount > -6 && amount < 6 && stack_len(*a) < 6)
	{
		sort_5(a, b);
		rotate_high_to_bottom(a);
	}
	else if ((amount == -6 || amount == 6) && stack_len(*a) == 6)
	{
		send_command("pb", a, b);
		sort_5(a, b);
		insert_in_place(a, b);
		rotate_high_to_bottom(a);
	}
	return (0);
}

int	quicksort_left(t_stack **a, t_stack **b, int amount)
{
	unsigned int	amt_moved;

	if (stack_is_sorted(*a) || amount == 0)
		return (0);
	if (ft_abs(amount) <= 6 && (stack_len(*a) <= 6 || ft_abs(amount) < 4))
		return (quicksort_left_finish(a, b, amount));
	else if (amount == stack_len(*a) && stack_len(*b) == 0)
	{
		amt_moved = push_lowest_x_double(a, b, (unsigned int)ft_abs(amount));
		quicksort_left(a, b, (-1) * (amount - amt_moved));
		quicksort_right(a, b, (amt_moved / 2) + (amt_moved % 2));
		quicksort_right(a, b, (amt_moved / 2));
		return (0);
	}
	if (amount > 0 || ft_abs(amount) == (unsigned int)stack_len(*a))
		amt_moved = push_lowest_x(a, b, ft_abs(amount));
	else
		amt_moved = push_lowest_x_rev(a, b, ft_abs(amount));
	if (amount < 0)
		quicksort_left(a, b, ft_abs(amount) - amt_moved);
	else
		quicksort_left(a, b, (-1) * (amount - amt_moved));
	quicksort_right(a, b, amt_moved);
	return (0);
}

int	quicksort(t_stack **a, t_stack **b)
{
	return (quicksort_left(a, b, stack_len(*a)));
}
