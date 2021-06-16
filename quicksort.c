#include "push_swap.h"
#include <stdio.h> //debug only

void	insert_in_place(t_stack **a, t_stack**b);

float	get_pivot(t_stack *a, int limit)
{
	float	median;
	int	lower;
	int	higher;
	t_stack	*index;
	int	i;

	if (limit == 0)
		return (a->value);
	median = a->value;
	while (1)
	{
		lower = 0;
		higher = 0;
		i = 0;
		index = a;
		while (index && i < limit)
		{
			if (index->value < median)
				++lower;
			if (index->value > median)
				++higher;
			index = index->next;
			++i;
		}
		if (lower == higher)
			return (median);
		if (lower == higher - 1 || higher == lower - 1)
		{
			return (median + higher - lower);
		}
		if (higher > lower)
			++median;
		else if (higher < lower)
			--median;
	}
	return (median);
}

int	quicksort(t_stack **a, t_stack **b)
{
	float pivot;
	int	limit;
	int	i;
	int	amt_skipped;
	int	amt_sorted;

	if (!a || !b)
		return (-1);
	amt_sorted = 0;
	while (!stack_is_ordered(*a)) //|| stack_len(*b))
	{
		limit = stack_len(*a) - amt_sorted;
		pivot = get_pivot(*a, limit);
		printf("Pivot = %f\n", pivot);
		i = 0;
		amt_skipped = 0;
		while (i < limit)
		{
			if ((*a)->value < pivot)
			{
				send_command("pb", a,b);
			}
			else
			{
				send_command("ra", a, b);
				++amt_skipped;
			}
			++i;
		}
		while (amt_sorted && amt_skipped)
		{
			send_command("rra", a, b);
			--amt_skipped;
		}
	}
	if (stack_len(*b))
	{
		take_from_b(a, b);
		// start over
	}
	return (0);
}
