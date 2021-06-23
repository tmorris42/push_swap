#include <stdio.h> //DEBUG ONLY
#include "push_swap.h"

int	take_highest_6_rev(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	int		amt_moved;
	int		amt_skipped;
	int		lowhigh[2];

	if (!a || !b || !(*b))
		return (-1);
	if (x < 4)
		printf("ERROR take_highest x is neg or too low\n"); //
	amt_moved = 0;
	amt_skipped = 0;
	if (x > stack_len(*b))
		x = stack_len(*b);
	pivot = get_pivot_rev(*b, x, (*b)->value); //
	lowhigh_prev_x(*b, x, pivot, &lowhigh[0]);
	while (b && (*b) && (amt_skipped + amt_moved < x))
	{
		send_command("rrb", a, b);
		if ((*b)->value > pivot)
		{
			send_command("pa", a, b);
			if ((*a)->value == lowhigh[0] && (*a)->next->value != lowhigh[1] && amt_moved < 2)
				send_command("ra", a, b); //could also check if "rb" happens next
			else if (amt_moved > 1 && (*a)->value > (*a)->next->value)
				send_command("sa", a, b); //could ss be useful here ever?
			++amt_moved;
		}
		else
		{
			++amt_skipped;
		}
	}
	if (stack_last(*a)->value == lowhigh[0])
		send_command("rra", a, b);
	return (amt_moved);
}

int	take_highest_x_rev(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack	*cursor;
	int		amt_moved;
	int		amt_skipped;

	if (x == 6)
		return (take_highest_6_rev(a, b, x));
	if (!a || !b || !(*b))
		return (-1);
	if (x < 0)
		printf("ERROR take_highest x is neg\n"); //
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

int	take_highest_6(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	int		amt_moved;
	int		amt_skipped;
	int		lowhigh[2];

	if (!a || !b || !(*b))
		return (-1);
	if (x < 4)
		printf("ERROR take_highest x is neg or too low\n"); //
	amt_moved = 0;
	amt_skipped = 0;
	if (x > stack_len(*b))
		x = stack_len(*b);
	pivot = get_pivot(*b, x, (*b)->value);
	lowhigh_next_x(*b, x, pivot, &lowhigh[0]);
	while (b && (*b) && (amt_skipped + amt_moved < x))
	{
		if ((*b)->value > pivot)
		{
			send_command("pa", a, b);
			if ((*a)->value == lowhigh[0] && (*a)->next->value != lowhigh[1] && amt_moved < 2)
				send_command("ra", a, b); //could also check if "rb" happens next
			else if (amt_moved > 1 && (*a)->value > (*a)->next->value)
				send_command("sa", a, b); //could ss be useful here ever?
			++amt_moved;
		}
		else
		{
			send_command("rb", a, b);
			++amt_skipped;
		}
	}
	if (stack_last(*a)->value == lowhigh[0])
		send_command("rra", a, b);
	return (amt_moved);
}

int	take_highest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack	*cursor;
	int		amt_moved;
	int		amt_skipped;

	if (x == 6)
		return (take_highest_6(a, b, x));
	if (!a || !b || !(*b))
		return (-1);
	if (x < 4)
		printf("ERROR take_highest x is neg or too low\n"); //
	amt_moved = 0;
	amt_skipped = 0;
	if (x > stack_len(*b))
		x = stack_len(*b);
	pivot = get_pivot(*b, x, (*b)->value); //
	cursor = (*b);
	while (cursor && (amt_skipped + amt_moved < x))
	{
		cursor = (*b);
		if (cursor->value > pivot)
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
