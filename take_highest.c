#include <stdio.h> //DEBUG ONLY
#include "push_swap.h"

int	take_highest_x_rev(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack	*cursor;
	int		amt_moved;
	int		amt_skipped;

	if (!a || !b || !(*b) || x < 0)
		return (0);
	if (x == 1)
	{
		send_command("rrb", a, b);
		send_command("pa", a, b);
		return (1);
	}
	amt_moved = 0;
	amt_skipped = 0;
	if (x > stack_len(*b))
		x = stack_len(*b);
	pivot = get_pivot_rev(*b, x, (*b)->value);
	while (x < 3 && amt_moved < x)
	{
		insert_in_place(a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		++amt_moved;
	}
	if (x < 4)
		return (amt_moved);
	cursor = (*b);
	while (cursor && amt_skipped + amt_moved < x)
	{
		send_command("rrb", a, b);
		cursor = (*b);
		if (cursor->value > pivot)
		{
			send_command("pa", a, b);
			++amt_moved;
		}
		else
		{
			++amt_skipped;
		}
	}
	return (amt_moved);
}

int	take_highest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	int		amt_moved;
	int		amt_skipped;

	if (!a || !b || !(*b) || x < 4)
		return (-1);
	amt_moved = 0;
	amt_skipped = 0;
	x = ft_min(x, stack_len(*b));
	pivot = get_pivot(*b, x, (*b)->value);
	while ((*b) && (amt_skipped + amt_moved < x))
	{
		if ((*b)->value > pivot)
		{
			send_command("pa", a, b);
			++amt_moved;
		}
		else
		{
			send_command("rb", a, b);
			++amt_skipped;
		}
	}
	return (amt_moved);
}
