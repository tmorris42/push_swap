/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:56:43 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/15 14:33:27 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> //debug only

void	get_low_high(t_stack *a, int *low, int *high)
{
	int		l;
	int		h;

	if (!a)
		return ;
	l = a->value;
	h = a->value;
	while (a)
	{
		l = ft_min(l, a->value);
		h = ft_max(h, a->value);
		a = a->next;
	}
	*low = l;
	*high = h;
}

int	find_index(t_stack **stack, int value)
{
	t_stack	*index;
	int		i;
	int		high;
	int		low;
	t_stack	*last;

	get_low_high(*stack, &low, &high);
	i = 0;
	index = *stack;
	last = stack_last(*stack);
	if (value > high && last->value == high)
		return (0);
	while (index)
	{
		if ((value < low || value > high) && index->value == high)
		{
			++i;
			index = NULL;
			break ;
		}
		else if (value <= index->value && value > last->value)
			break ;
		last = index;
		index = index->next;
		++i;
	}
	return (i);
}

int	find_index_low(t_stack **stack, int value)
{
	t_stack	*index;
	int		i;
	int		high;
	int		low;
	t_stack	*last;

	get_low_high(*stack, &low, &high);
	i = 0;
	index = *stack;
	last = stack_last(*stack);
	if (value > high && last->value == high)
		return (0);
	while (index)
	{
		if ((value < low || value > high) && index->value == low)
		{
			++i;
			index = NULL;
			break ;
		}
		else if (value >= index->value && value < last->value)
			break ;
		last = index;
		index = index->next;
		++i;
	}
	return (i);
}

void	rotate_to_index(t_stack **stack, int i)
{
	int		len;

	len = stack_len(*stack);
	if (len == 0)
		len = 0;
	if (2 * i > len)
		i = i - len;
	while (i != 0)
	{
		if (i < 0)
		{
			send_command("rra", stack, NULL);
			++i;
		}
		else
		{
			send_command("ra", stack, NULL);
			--i;
		}
	}
}

void	rotate_b_to_index(t_stack **stack, int i)
{
	int		len;

	len = stack_len(*stack);
	if (len == 0)
		len = 0;
	if (2 * i > len)
		i = i - len;
	while (i != 0)
	{
		if (i < 0)
		{
			send_command("rrb", NULL, stack);
			++i;
		}
		else
		{
			send_command("rb", NULL, stack);
			--i;
		}
	}
}

void	insert_in_place(t_stack **a, t_stack **b)
{
	int	i;

	i = find_index(a, (*b)->value);
	rotate_to_index(a, i);
	send_command("pa", a, b);
}

void	insert_b_in_place(t_stack **a, t_stack **b)
{
	int	i;

	i = find_index_low(b, (*a)->value);
	rotate_b_to_index(b, i);
	send_command("pb", a, b);
}

void	rotate_high_to_bottom(t_stack **a)
{
	int		high;
	int		low;

	get_low_high(*a, &low, &high);
	low = find_index(a, high + 1);
	rotate_to_index(a, low);
}

int	sort_3(t_stack **a, t_stack **b)
{
	int		first;
	int		second;
	int		third;

	if (stack_is_ordered(*a))
		return (0);
	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first > second && first > third && third > second)
		send_command("ra", a, b);
	else if (second > first && second > third && first > third)
		send_command("rra", a, b);
	else
	{
		send_command("sa", a, b);
		return (sort_3(a, b));
	}
	return (0);
}

int	sort_5(t_stack **a, t_stack **b)
{
	send_command("pb", a, b);
	send_command("pb", a, b);
	sort_3(a, b);
	insert_in_place(a, b);
	insert_in_place(a, b);
	return (0);
}

int	how_far_from_top(t_stack *a, int value)
{
	int		len;
	int		i;

	len = stack_len(a);
	i = find_index(&a, value);
	if (2 * i > len)
		i = ft_abs(i - len);
	return (i);
}

int	get_closest_to_top(t_stack *a, t_stack *b)
{
	int		i;
	int		dist;
	int		prev_dist;
	int		best_i;

	i = 0;
	prev_dist = stack_len(a);
	best_i = 0;
	while (b)
	{
		dist = how_far_from_top(a, b->value) + i;
		if (dist < prev_dist)
		{
			prev_dist = dist;
			best_i = i;
		}
		++i;
		b = b->next;
	}
	return (best_i);
}

int	get_closest_to_top_under(t_stack *a, t_stack *b, int target)
{
	int		i;
	int		dist;
	int		prev_dist;
	int		best_i;

	i = 0;
	prev_dist = stack_len(a);
	best_i = 0;
	while (b)
	{
		if (b->value > target)
			continue ;
		dist = how_far_from_top(a, b->value) + i;
		if (dist < prev_dist)
		{
			prev_dist = dist;
			best_i = i;
		}
		++i;
		b = b->next;
	}
	return (best_i);
}

int	stack_has_above(t_stack **a, int value)
{
	t_stack	*stack;
	int		i;
	int		bot_i;

	bot_i = -1;
	i = 0;
	if (!a || !(*a))
		return (0);
	stack = (*a);
	while (stack)
	{
		if (stack->value < value)
			bot_i = i;
		stack = stack->next;
		++i;
	}
	return (bot_i);
}

int	stack_has_below(t_stack **a, int value)
{
	t_stack	*stack;
	int		i;

	i = 0;
	if (!a || !(*a))
		return (0);
	stack = (*a);
	while (stack)
	{
		if (stack->value < value)
			return (i);
		++i;
		stack = stack->next;
	}
	return (0);
}

int	which_is_closest(t_stack *a, int top, int bot)
{
	int		len;

	len = stack_len(a);
	if (2 * top > len || (int)ft_abs(bot - len) < top)
		return (bot);
	return (top);
}

int	hold_sort_mod(t_stack **a, t_stack **b)
{
	int		len_a;
	int		high;
	int		i;
	int		avg;

	if (!a || !b)
		return (-1);
	get_low_high(*a, &len_a, &high);
	avg = (high + len_a) / 2;
	len_a = stack_len(*a);
	if (len_a < 4)
	{
		sort_3(a, b);
		rotate_high_to_bottom(a);
	}
	high = stack_last(*a)->value;
	while (!stack_is_ordered(*a))
	{
		if ((*a)->value > high)
		{
			high = (*a)->value;
			if ((*b) && (*b)->value < avg)
				send_command("rr", a, b);
			else
				send_command("ra", a, b);
		}
		else if ((*b) && (*b)->next && (*b)->value < avg && (*b)->next->value >= avg)
			send_command("rb", a, b);
		send_command("pb", a, b);
	}
	while (*b)
	{
		i = get_closest_to_top(*a, *b);
		rotate_b_to_index(b, i);
		insert_in_place(a, b);
	}
	rotate_high_to_bottom(a);
	return (0);
}

int	has_average_values(t_stack **a, int high_qtr, int low_qtr)
{
	t_stack	*index;
	int		i;
	int		first;
	int		last;
	int		len;

	len = stack_len(*a);
	index = (*a);
	i = 0;
	first = 0;
	last = 0;
	while (index)
	{
		if (index->value <= high_qtr && index->value >= low_qtr)
		{
			if (i == 0)
				return (1);
			else if (!first)
				first = i;
			else
				last = i;
		}
		index = index->next;
	}
	if (!first && !last)
		return (0);
	first = which_is_closest(*a, first, last);
	if (2 * first > len)
		return (-1);
	return (1);
}

int	low_high_trigger(t_stack **a, t_stack **b, int low, int high)
{
	int		stop;
	int		avg;
	int		direction;

	get_low_high(*a, &stop, &avg);
	avg = (avg + stop) / 2;
	while (!stack_is_ordered(*a))
	{
		direction = has_average_values(a, high, low);
		if (direction == 0)
			break ;
		if (direction > 0)
		{
			if ((*a)->value > high || (*a)->value < low)
			{
				if ((*b) && (*b)->value < avg)
					send_command("rr", a, b);
				else
					send_command("ra", a, b);
			}
			else if ((*b) && (*b)->next && (*b)->value < avg && (*b)->next->value >= avg)
				send_command("rb", a, b);
			else
				send_command("pb", a, b);
		}
		else if (direction < 0)
		{
			if ((*a)->value > high || (*a)->value < low)
			{
				if ((*b) && (*b)->value < avg)
					send_command("rrr", a, b);
				else
					send_command("rra", a, b);
			}
			else if ((*b) && (*b)->next && (*b)->value < avg && (*b)->next->value >= avg)
				send_command("rrb", a, b);
			else
				send_command("pb", a, b);
		}
	}
	return (0);
}

int	four_hold_sort_mod(t_stack **a, t_stack **b)
{
	int		len_a;
	int		high;
	int		avg;
	int		high_qtr;
	int		low_qtr;

	if (!a || !b)
		return (-1);
	get_low_high(*a, &len_a, &high);
	avg = (high + len_a) / 2;
	high_qtr = (high + avg) / 2;
	low_qtr = (len_a + avg) / 2;
	len_a = stack_len(*a);
	high = stack_last(*a)->value;
	return (low_high_trigger(a, b, low_qtr, high_qtr));
}

int	five_hold_sort_mod(t_stack **a, t_stack **b)
{
	int		low;
	int		high;

	if (!a || !b)
		return (-1);
	get_low_high(*a, &low, &high);
	low_high_trigger(a, b, ((3 * high) + low) / 7, ((4 * high) + low) / 7);
	low_high_trigger(a, b, ((2 * high) + low) / 7, ((5 * high) + low) / 7);
	low_high_trigger(a, b, ((1 * high) + low) / 7, ((6 * high) + low) / 7);
	return (0);
}

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
	x = x / 2; // change this is pivot is updated to modify x properly
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

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		len;

	b = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (-1);
	len = stack_len(a);
	if (len < 4)
		sort_3(&a, &b);
	else if (len < 6)
		sort_5(&a, &b);
/*	else if (len < 50)i
	{
		four_hold_sort_mod(&a, &b);
		hold_sort_mod(&a, &b);
	}	*/
	else
	{
		quicksort(&a, &b);
	}
	rotate_high_to_bottom(&a);
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
