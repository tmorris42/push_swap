/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:53:22 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/23 11:57:40 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	get_pivot(t_stack *a, int limit, float median)
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
		if (index->value <= median)
			++lower;
		else
			++higher;
		index = index->next;
		++i;
	}
	if (lower == higher || lower == higher - 1 || higher == lower - 1)
		return (median);
	if (higher > lower)
		return (get_pivot(a, limit, median + 1));
	return (get_pivot(a, limit, median - 1));
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

float	get_pivot_rev(t_stack *a, int limit, float median)
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
		return (median + higher - lower);
	if (higher > lower)
		return (get_pivot_rev(a, limit, median + 1));
	return (get_pivot_rev(a, limit, median - 1));
}
