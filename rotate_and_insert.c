#include "push_swap.h"

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

int	find_index(t_stack *index, int value)
{
	int		i;
	int		high;
	int		low;
	t_stack	*last;

	get_low_high(index, &low, &high);
	i = 0;
	last = stack_last(index);
	if (value > high && last->value == high)
		return (0);
	while (index)
	{
		if ((value < low || value > high) && index->value == high)
		{
			++i;
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
	int	i;

	i = find_index(*a, (*b)->value);
	rotate_to_index(a, i);
	send_command("pa", a, b);
}

void	rotate_high_to_bottom(t_stack **a)
{
	int		high;
	int		low;

	if (!a || !(*a))
		return ;
	get_low_high(*a, &low, &high);
	if (stack_last(*a)->value == high)
		return ;
	low = find_index(*a, high + 1);
	rotate_to_index(a, low);
}
