#include "push_swap.h"

int	take_highest_x_rev(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	int		amt_moved;
	int		amt_skipped;

	if (!a || !b || !(*b) || x < 0)
		return (0);
	amt_moved = 0;
	amt_skipped = 0;
	x = ft_min(x, stack_len(*b));
	pivot = get_pivot_rev(*b, x, (*b)->value);
	while ((*b) && amt_skipped + amt_moved < x)
	{
		send_command("rrb", a, b);
		if ((*b)->value > pivot)
		{
			send_command("pa", a, b);
			++amt_moved;
		}
		else
			++amt_skipped;
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
