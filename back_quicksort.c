#include "push_swap.h"
#include <stdio.h> //debug only

void	insert_in_place(t_stack **a, t_stack**b);

int	get_pivot(t_stack *a, int *limit)
{
	int	median;
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
		while (index && i < *limit)
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

int	pass_lowest_x(t_stack **a, t_stack **b, int x)
{
	int	pivot;
	t_stack *stop;
	t_stack	*cursor;
	t_stack	*next;
	int	amt_moved;

	if (!a || !b)
		return (-1);
	amt_moved = 0;
	stop = NULL;
	pivot = get_pivot(*a, &x); //
	//printf("Pivot = %d\n", pivot);
	cursor = (*a);
	while (cursor)
	{
		if (!stop && cursor->value > pivot)
			stop = cursor;
		next = cursor->next;
		if (cursor->value < pivot)
		{
			send_command("pb", a, b);
			++amt_moved;
		}
		else
			send_command("ra", a, b);
		cursor = next;
		if (cursor == stop)
			return (amt_moved);
	}
	return (amt_moved);
}

int	take_highest_x(t_stack **a, t_stack **b, int x)
{
	int	pivot;
	t_stack *stop;
	t_stack	*cursor;
	t_stack	*next;
	int	amt_moved;
	int	amt_skipped;

	if (!a || !b)
		return (-1);
	amt_moved = 0;
	amt_skipped = 0;
	if (x < 3)
	{
		while (x > 0)
		{
			insert_in_place(a, b);
			++amt_moved;
			--x;
		}
	}
	else
	{
		stop = NULL;
		pivot = get_pivot(*b, &x); //
		cursor = (*a);
		while (cursor && amt_skipped + amt_moved < x)
		{
			if (!stop && cursor->value > pivot)
				stop = cursor;
			next = cursor->next;
			if (cursor->value >= pivot)
			{
				send_command("pa", a, b);
				++amt_moved;
			}
			else
			{
				send_command("rb", a, b);
				++amt_skipped;
//				stack_print(*a, *b);
//				printf("amt_skipped = %d, x = %d, pivot = %d, value=%d\n", amt_skipped, x, pivot, (*b)->value); //DEL
			}
		}
	}
	return (amt_moved);
}

int	quicksort(t_stack **a, t_stack **b)
{
	int	amt_sorted;
	int	amt_moved;
	t_stack	*tracker;
	t_stack	*temp;

	amt_sorted = 0;
	amt_moved = 0;
	tracker = NULL;
	while (a && b && (!stack_is_ordered(*a) || stack_len(*b)))
	{
		while (stack_len(*a) - amt_sorted > 2)
		{
			amt_moved = pass_lowest_x(a, b, stack_len(*a) - amt_sorted);
			temp = stack_new(amt_moved);
			if (!temp)
				return (-1); //clear tracker first
			stack_add_front(&tracker, temp);
//			stack_print(tracker, NULL);
			temp = NULL;
		}
		if (stack_len(*a) > 1 && (*a)->value > (*a)->next->value)
			send_command("sa", a, b);
		if (stack_is_ordered(*a))
			amt_sorted = stack_len(*a);
		// here we should take back a chunk from b
		if (tracker)
		{
			tracker->value -= take_highest_x(a, b, tracker->value);
			if (tracker->value < 1)
			{
				temp = tracker;
				tracker = tracker->next;
				free(temp);
				temp = NULL;
			}
		}
	}
	while (*b)
	{
		insert_in_place(a, b);
	}
	return (0);
}
