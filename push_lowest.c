#include <stdio.h> //DEBUG ONLY
#include "push_swap.h"

unsigned int	push_lowest_x_rev(t_stack **a, t_stack **b, unsigned int x)
{
	float			pivot;
	t_stack			*cursor;
	unsigned int	amt_moved;
	int				amt_skipped;

	if (!a || !(*a) || !b)
		return (-1);
	amt_moved = 0;
	amt_skipped = 0;
	pivot = get_pivot_rev(*a, x, (*a)->value);
	cursor = (*a);
	while (cursor && amt_moved + amt_skipped < x)
	{
		send_command("rra", a, b);
		cursor = (*a);
		if (cursor->value <= pivot)
		{
			send_command("pb", a, b);
			++amt_moved;
		}
		else
			++amt_skipped;
	}
	return (amt_moved);
}

unsigned int	push_lowest_x_double(t_stack **a, t_stack **b, unsigned int x)
{
	float			pivot;
	float			upper;
	unsigned int	amt_moved;
	unsigned int	amt_skipped;

	if (!a || !b || x > (unsigned int)stack_len(*a))
		return (0);
	amt_moved = 0;
	amt_skipped = 0;
	pivot = get_pivot(*a, x, (*a)->value);
	upper = get_upper_pivot(*a, pivot);
	while ((*a) && amt_moved + amt_skipped < x)
	{
		if ((*a)->value < pivot)
		{
			send_command("pb", a, b);
			if ((*b)->value < upper && (*b)->next && (*b)->next->value >= upper)
				send_command("rb", a, b);
			++amt_moved;
			continue ;
		}
		send_command("ra", a, b);
		++amt_skipped;
	}
	return (amt_moved);
}

unsigned int	push_lowest_x(t_stack **a, t_stack **b, unsigned int x)
{
	float			pivot;
	unsigned int	amt_moved;
	unsigned int	amt_skipped;

	if (!a || !(*a) || !b || x > (unsigned int)stack_len(*a))
		return (0);
	amt_moved = 0;
	amt_skipped = 0;
	pivot = get_pivot(*a, x, (*a)->value);
	while ((*a) && amt_moved + amt_skipped < x)
	{
		if ((*a)->value <= pivot)
		{
			send_command("pb", a, b);
			++amt_moved;
		}
		else
		{
			send_command("ra", a, b);
			++amt_skipped;
		}
	}
	return (amt_moved);
}
