#include "push_swap.h"

float	get_pivot(t_stack *a, int limit, float guess)
{
	int		lower;
	int		higher;
	t_stack	*index;
	int		i;

	if (!a || limit == 0)
		return (0);
	lower = 0;
	higher = 0;
	i = 0;
	index = a;
	while (index && i < limit)
	{
		if (index->value <= guess)
			++lower;
		else
			++higher;
		index = index->next;
		++i;
	}
	if (lower == higher || lower == higher - 1 || higher == lower - 1)
		return (guess);
	if (higher > lower)
		return (get_pivot(a, limit, guess + 1));
	return (get_pivot(a, limit, guess - 1));
}

float	get_upper_pivot(t_stack *a, float pivot, float guess)
{
	int		lower;
	int		higher;
	t_stack	*index;

	if (!a)
		return (0);
	lower = 0;
	higher = 0;
	index = a;
	while (index)
	{
		if (index->value < pivot && index->value < guess)
			++lower;
		else if (index->value < pivot && index->value >= guess)
			++higher;
		index = index->next;
	}
	if (lower == higher)
		return (guess);
	if (lower == higher - 1)
		return (guess);
	if (higher > lower)
		return (get_upper_pivot(a, pivot, guess + 1));
	return (get_upper_pivot(a, pivot, guess - 1));
}

float	get_pivot_rev(t_stack *a, int limit, float guess)
{
	int		lower;
	int		higher;
	t_stack	*index;
	int		i;

	if (!a || limit == 0)
		return (0);
	lower = 0;
	higher = 0;
	i = 0;
	index = stack_last(a);
	while (index && i < limit)
	{
		if (index->value < guess)
			++lower;
		if (index->value > guess)
			++higher;
		index = index->prev;
		++i;
	}
	if (lower == higher || lower == higher - 1 || higher == lower - 1)
		return (guess + higher - lower);
	if (higher > lower)
		return (get_pivot_rev(a, limit, guess + 1));
	return (get_pivot_rev(a, limit, guess - 1));
}
