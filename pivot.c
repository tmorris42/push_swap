#include "push_swap.h"

float	get_pivot(t_stack *a, int limit)
{
	float	median;
	int		lower;
	int		higher;
	t_stack	*index;
	int		i;

	if (!a || limit == 0)
		return (0);
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
		if (lower == higher || lower == higher - 1 || higher == lower - 1)
			return (median);
		if (higher > lower)
			++median;
		else if (higher < lower)
			--median;
	}
	return (median);
}

float	get_upper_pivot(t_stack *a, float pivot)
{
	float	median;
	int		lower;
	int		higher;
	t_stack	*index;

	if (!a)
		return (0);
	median = a->value;
	while (1)
	{
		lower = 0;
		higher = 0;
		index = a;
		while (index)
		{
			if (index->value >= pivot)
			{
			}
			else if (index->value < median)
				++lower;
			else if (index->value >= median)
				++higher;
			index = index->next;
		}
		if (lower == higher)
			return (median);
		if (lower == higher - 1)
			return (median);
		if (higher > lower)
			++median;
		else if (higher < lower)
			--median;
	}
	return (median);
}

float	get_pivot_rev(t_stack *a, int limit)
{
	float	median;
	int		lower;
	int		higher;
	t_stack	*index;
	int		i;

	if (!a)
		return (0);
	if (limit == 0)
		return (a->value);
	median = stack_last(a)->value;
	while (1)
	{
		lower = 0;
		higher = 0;
		i = 0;
		index = stack_last(a);
		while (index && i < limit)
		{
			if (index->value < median)
				++lower;
			if (index->value > median)
				++higher;
			index = index->prev;
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
