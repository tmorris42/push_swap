#include "push_swap.h"
#include <stdio.h> //debug only

void	insert_in_place(t_stack **a, t_stack**b);
int	quicksort_left(t_stack **a, t_stack **b, int amount);
void	rotate_high_to_bottom(t_stack **a);

float	get_pivot(t_stack *a, int limit)
{
	float	median;
	int	lower;
	int	higher;
	t_stack	*index;
	int	i;

	if (!a)
		return (0);
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

/*int	quicksort_iter(t_stack **a, t_stack **b)
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
}*/

int	pass_lowest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack *stop;
	t_stack	*cursor;
	t_stack	*next;
	int	amt_moved;
	int	amt_skipped;

	if (!a || !b)
		return (-1);
	if (x < 0)
		printf("ERROR pass_lowest x is neg\n");
	amt_moved = 0;
	amt_skipped = 0;
	stop = NULL;
	pivot = get_pivot(*a, x); //
	//printf("Pivot = %d\n", pivot);
	cursor = (*a);
	while (cursor && amt_moved + amt_skipped < x)
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
		{
			send_command("ra", a, b);
			++amt_skipped;
		}
		cursor = next;
		if (cursor == stop)
			return (amt_moved);
	}
	while (amt_skipped > 0)
	{
		send_command("rra", a, b);
		--amt_skipped;
	}
	return (amt_moved);
}

int	take_highest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack *stop;
	t_stack	*cursor;
	t_stack	*next;
	int	amt_moved;
	int	amt_skipped;

	if (!a || !b)
		return (-1);
	if (x < 0)
		printf("ERROR take_highest x is neg\n");
	amt_moved = 0;
	amt_skipped = 0;
	stop = NULL;
	pivot = get_pivot(*b, x); //
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
	while (amt_skipped > 0)
	{
		send_command("rrb", a, b);
		--amt_skipped;
	}
	return (amt_moved);
}

int	quicksort_right(t_stack **a, t_stack **b, int amount)
{
	int	amt_moved;

	amt_moved = 0;
	if (amount == 0 || !stack_len(*b))
		return (0);
	if (amount == 1)
		send_command("pa", a, b);
	else
	{
		amt_moved = take_highest_x(a, b, amount);
		//move from right to left (amount / 2))
		//	remember that if amount < 0: cmd = "rrb" else "rb"
		quicksort_left(a, b, amt_moved);
		quicksort_right(a, b, amount - amt_moved);
	}
	return (0);
}

int	quicksort_left(t_stack **a, t_stack **b, int amount)
{
	int	amt_moved;

	amt_moved = 0;
	if (stack_is_sorted(*a) || amount == 0)
		return (0);
	if (amount > -3 && amount < 3)
	{
		//swap the top two, or pull down and swap the top two
		if (amount < 0)
			send_command("rra", a, b);
		send_command("sa", a, b);
	}
	else
	{
		amt_moved = pass_lowest_x(a, b, amount);
		//move from left to right (amount - (amount / 2))
		//	remember that if amount < 0: cmd = "rra" else "ra"
		quicksort_left(a, b, amount - amt_moved);
//		printf("amt_moved == %d, stack_len(a) == %d\n", amt_moved, stack_len(*a));
//		stack_print(*a, *b);
//		exit(0); //TESTING
		quicksort_right(a, b, amt_moved);
	}
	return (0);
}

int	quicksort_recursive(t_stack **a, t_stack **b)
{
	quicksort_left(a, b, stack_len(*a));
	return (0);
}

int	quicksort(t_stack **a, t_stack **b)
{
	return (quicksort_recursive(a, b));
}
