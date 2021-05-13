/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:56:43 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/13 16:05:17 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> //debug only

void	rough_sort(t_stack **a, t_stack **b)
{
	int		len_a;
	int		sorted;

	len_a = stack_len(*a);
	if (len_a < 2)
		return ;
	sorted = ((stack_is_sorted(*a)) && ((*b) == NULL));
	while (!sorted)
	{
		if ((*a) && !stack_is_sorted(*a))
		{
			if ((*a)->value < (*a)->next->value)
			{
				if (!(*b) || ((*b)->value < (*a)->value))
				{
					ft_putstr("pb\n");
					stack_push(a, b);
				}
				else
			{
					ft_putstr("pa\n");
					stack_push(b, a);
				}
			}
			else
			{
				ft_putstr("sa\n");
				stack_swap(a);
			}
		}
		else
		{
			ft_putstr("pa\n");
			stack_push(b, a);
		}
		sorted = ((stack_is_sorted(*a)) && ((*b) == NULL));
	}
}

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

void	stack_split_by(t_stack **a, t_stack **b, int median)
{
	int		len;

	len = stack_len(*a);

	ft_putstr("median: ");
	ft_putnbr(median);
	ft_putchar('\n');
	while (len > 0)
	{
		if ((*a)->value < median)
		{
			printf("%d is less than %d\n", (*a)->value, median);
			send_command("pb", a, b);
		}
		else
			send_command("ra", a, b);
		--len;
	}
}

void	find_spot(t_stack **stack, int value)
{
	t_stack	*index;
	int		i;
	int		high;

	i = 0;
	index = *stack;
	high = stack_last(index)->value;
	while(index)
	{
		if (value < index->value || value > high)
			break;
		index = index->next;
		++i;
	}
	while (i)
	{
//		if (i < stack_len(*stack))
		send_command("ra", stack, NULL);
		--i;
	}
}

int		find_index(t_stack **stack, int value)
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
	while(index)
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

int		find_index_low(t_stack **stack, int value)
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
	while(index)
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
	int		i;

	i = find_index(a, (*b)->value);
	rotate_to_index(a, i);
	send_command("pa", a, b);	
}

void	insert_b_in_place(t_stack **a, t_stack **b)
{
	int		i;

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

int		sort_3(t_stack **a, t_stack **b)
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

int		sort_4(t_stack **a, t_stack **b)
{
	send_command("pb", a, b);
	sort_3(a, b);
	insert_in_place(a, b);
	return (0);
}

int		sort_5(t_stack **a, t_stack **b)
{
	send_command("pb", a, b);
	send_command("pb", a, b);
	sort_3(a, b);
	insert_in_place(a, b);
	insert_in_place(a, b);
	return (0);
}

int		how_far_from_top(t_stack *a, int value)
{
	int		len;
	int		i;

	len = stack_len(a);
	i = find_index(&a, value);
	if (2 * i > len)
		i = ft_abs(i - len);
	return (i);
}

int		get_closest_to_top(t_stack *a, t_stack *b)
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

int		get_closest_to_top_under(t_stack *a, t_stack *b, int target)
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

int		stack_has_above(t_stack **a, int value)
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

int		stack_has_below(t_stack **a, int value)
{
	t_stack	*stack;

	if (!a || !(*a))
		return (0);
	stack = (*a);
	while (stack)
	{
		if (stack->value < value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int		which_is_closest(t_stack *a, int top, int bot)
{
	int		len;

	len = stack_len(a);
	if (2 * top > len || (int)ft_abs(bot - len) < top)
		return (bot);
	return (top);
}

int		sort_50(t_stack **a, t_stack **b)
{
	int		len;
	int		high;
	int		low;
	int		i;
	int		target;
	int		top_hold;

	get_low_high(*a, &low, &high);
	target = high - (4 * (high - low) / 5);
	len = stack_len(*a);
	while (len > 3)
	{
		top_hold = stack_has_below(a, target);
		if (top_hold == -1)
		{
			if (target < high - (2 * (high - low) / 5))
				target = high - (1 * (high - low) / 5);
			else if (target < high - (3 * (high - low) / 5))
				target = high - (2 * (high - low) / 5);
			else if (target < high - (4 * (high - low) / 5))
				target = high - (3 * (high - low) / 5);
			else
				target = high + 1;
			continue ;
		}
		if ((*a)->value >= target)
		{
			send_command("ra", a, b);
		}
		insert_b_in_place(a, b);
		--len;
	}
	sort_3(a, b);
	while (*b)
	{
		i = get_closest_to_top(*a, *b);
		rotate_b_to_index(b, i);
		insert_in_place(a, b);
	}
	return (0);
}

int		sort_100(t_stack **a, t_stack **b)
{
	int		len_a;
	int		len_b;
	int		high;
	int		low;
	int		i;
	int		target;
	int		top_hold;
//	int		bot_hold;

	get_low_high(*a, &low, &high);
	target = high - (4 * (high - low) / 5);
	len_a = stack_len(*a);
	len_b = stack_len(*b);
	if (len_b)
		len_b = len_b;
	while (len_a > 3)
	{
		top_hold = stack_has_below(a, target);
		if (top_hold == -1)
		{
			if (target < high - (2 * (high - low) / 5))
				target = high - (1 * (high - low) / 5);
			else if (target < high - (3 * (high - low) / 5))
				target = high - (2 * (high - low) / 5);
			else if (target < high - (4 * (high - low) / 5))
				target = high - (3 * (high - low) / 5);
			else
				target = high + 1;
			continue ;
		}
//		bot_hold = stack_has_above(a, target);
//		if ((*a)->value < (high + low) / 2)
	//		send_command("pb", a, b);
		if ((*a)->value >= target)
		{
			send_command("ra", a, b);
//			i = get_closest_to_top_under(*b, *a, target);
//			i = which_is_closest(*a, top_hold, bot_hold);
//			rotate_to_index(a, i);
		}
		insert_b_in_place(a, b);
		--len_a;
	}
	sort_3(a, b);
	while (*b)
	{
	//	if ((*b) && (*b)->next && how_far_from_top(a, (*b)->value) > how_far_from_top(a, (*b)->next->value))
	//		send_command("sb", a, b);
		i = get_closest_to_top(*a, *b);
		rotate_b_to_index(b, i);
		insert_in_place(a, b);
	}
	return (0);
}

int		sort_x(t_stack **a, t_stack **b)
{
	int		len;
	int		high;
	int		low;
	int		i;
	int		target;
	int		top_hold;
//	int		bot_hold;

	get_low_high(*a, &low, &high);
	target = high - (4 * (high - low) / 5);
	len = stack_len(*a);
	while (len > 3)
	{
		top_hold = stack_has_below(a, target);
		if (top_hold == -1)
		{
			if (target < high - (2 * (high - low) / 5))
				target = high - (1 * (high - low) / 5);
			else if (target < high - (3 * (high - low) / 5))
				target = high - (2 * (high - low) / 5);
			else if (target < high - (4 * (high - low) / 5))
				target = high - (3 * (high - low) / 5);
			else
				target = high + 1;
			continue ;
		}
//		bot_hold = stack_has_above(a, target);
//		if ((*a)->value < (high + low) / 2)
	//		send_command("pb", a, b);
		if ((*a)->value >= target)
		{
			send_command("ra", a, b);
//			i = get_closest_to_top_under(*b, *a, target);
//			i = which_is_closest(*a, top_hold, bot_hold);
//			rotate_to_index(a, i);
		}
		insert_b_in_place(a, b);
		--len;
	}
	sort_3(a, b);
	while (*b)
	{
	//	if ((*b) && (*b)->next && how_far_from_top(a, (*b)->value) > how_far_from_top(a, (*b)->next->value))
	//		send_command("sb", a, b);
		i = get_closest_to_top(*a, *b);
		rotate_b_to_index(b, i);
		insert_in_place(a, b);
	}
	return (0);
}

int		sort_min_max(t_stack **a, t_stack **b)
{
	int		low;
	int		high;
	int		len_a;
	int		sorted;

	len_a = stack_len(*a);
	if (len_a < 2)
		return (0);
	sorted = ((stack_is_sorted(*a)) && ((*b) == NULL));
	if (sorted)
		return (0);
	else if (len_a == 3)
		sort_3(a, b);
	else if (len_a == 4)
		sort_4(a, b);
	else if (len_a == 5)
		sort_5(a, b);
	else if (len_a <= 50)
		sort_50(a, b);
	else if (len_a <= 100)
		sort_100(a, b);
	else if (len_a > 100)
		sort_x(a, b); //temp jump to avoid segfault
	rotate_high_to_bottom(a);
	return (0);
	get_low_high(*a, &low, &high);
	stack_split_by(a, b, (high + low) / 2);
	while (!sorted)
	{
		if ((*a) && (*a)->next && (*a)->value > (*a)->next->value)
			send_command("sa", a, b);
		if ((*b) && (*b)->next && (*b)->value > (*b)->next->value)
			send_command("sb", a, b);

		sorted = ((stack_is_sorted(*a)) && ((*b) == NULL));
		sorted = 1; // ending loop
	}
	return (0);
}

int		bubble_sort(t_stack **a, t_stack **b)
{
	int		len_a;
	int		high;

	if (!a || !b)
		return (-1);
	get_low_high(*a, &len_a, &high);
	len_a = stack_len(*a);
	if (len_a < 4)
	{
		sort_3(a, b);
		rotate_high_to_bottom(a);
		return (0);
	}
	
	while (!stack_is_ordered(*a))
	{
		if ((*a)->value == high)
		{
			send_command("rra", a, b);
		}
		else if ((*a)->value > (*a)->next->value)
		{
			send_command("sa", a, b);
			send_command("ra", a, b);
		}
		else
		{
			send_command("rra", a, b);
		}
	}
	rotate_high_to_bottom(a);

	return (0);
}

int		hold_sort_mod(t_stack **a, t_stack **b)
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
//		return (0);
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
		{
			send_command("rb", a, b);
		}
//		else if ((*b) && (*a)->value > stack_last(*b)->value)
	//	{
	//		send_command("pb", a, b);
	//		send_command("rr", a, b);
	//	}
		if ((*a)->value > (*a)->next->value)
		{
//			insert_b_in_place(a, b);
			send_command("pb", a, b);
//			send_command("ra", a, b);
		}
		else
		{
//			insert_b_in_place(a, b);
			send_command("pb", a, b);
//			send_command("rb", a, b);
//			send_command("sa", a, b);
		}
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

int		finish_hold_sort_mod(t_stack **a, t_stack **b)
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
		{
			send_command("rb", a, b);
		}
		else
		{
			send_command("pb", a, b);
		}
	}
	while ((*b))
	{
		i = get_closest_to_top(*a, *b);
		rotate_b_to_index(b, i);
		insert_in_place(a, b);
	}
	rotate_high_to_bottom(a);

	return (0);
}

int		four_hold_sort_mod(t_stack **a, t_stack **b)
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
	if (len_a < 4)
	{
		sort_3(a, b);
		rotate_high_to_bottom(a);
		return (0);
	}
	high = stack_last(*a)->value;
	while ((*a)->value != high)
	{
		if ((*a)->value > high_qtr || (*a)->value < low_qtr)
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

	return (0);
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack *b;

	b = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (-1);
	//rough_sort(&a, &b);
	//sort_min_max(&a, &b);
	//bubble_sort(&a, &b);
	four_hold_sort_mod(&a, &b);
	hold_sort_mod(&a, &b);
//	finish_hold_sort_mod(&a, &b);
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
