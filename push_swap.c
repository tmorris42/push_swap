/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:56:43 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/12 11:23:15 by tmorris          ###   ########.fr       */
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
	t_stack	*last;

	get_low_high(*stack, &i, &high);
	i = 0;
	index = *stack;
	last = stack_last(*stack);
	if (value > high && last->value == high)
		return (0);
	while(index)
	{
		if (value > high && index->value == high)
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

void	insert_in_place(t_stack **a, t_stack **b)
{
	int		i;

	i = find_index(a, (*b)->value);
	rotate_to_index(a, i);
	send_command("pa", a, b);	
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

	if (stack_is_sorted(*a))
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
	rotate_high_to_bottom(a);
	return (0);
}

int		sort_5(t_stack **a, t_stack **b)
{
	send_command("pb", a, b);
	send_command("pb", a, b);
	sort_3(a, b);
	insert_in_place(a, b);
	insert_in_place(a, b);
	rotate_high_to_bottom(a);
	return (0);
}

int		sort_x(t_stack **a, t_stack **b)
{
	int		len;

	len = stack_len(*a);
	while (len > 3)
	{
		send_command("pb", a, b);
		--len;
	}
	sort_3(a, b);
	while (*b)
	{
		insert_in_place(a, b);
	}
	rotate_high_to_bottom(a);
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
	if (len_a == 3)
		return (sort_3(a, b));
	if (len_a == 4)
		return (sort_4(a, b));
	if (len_a == 5)
		return (sort_5(a, b));
	return (sort_x(a, b)); //temp jump to avoid segfault
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

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack *b;

	b = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (-1);
	//rough_sort(&a, &b);
	sort_min_max(&a, &b);
	return (0);
}
