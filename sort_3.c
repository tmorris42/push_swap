#include "push_swap.h"

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

void	put_top_3_rev(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

	if (amount < -3 || amount > -1)
		return ;
	first = stack_last(*b)->value;
	if (amount == -1)
	{
		send_command("rrb", a, b);
		send_command("pa", a, b);
		return ;
	}
	second = stack_last(*b)->prev->value;
	if (amount == -2)
	{
		send_command("rrb", a, b);
		if (first > second)
			send_command("pa", a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		if (first < second)
			send_command("pa", a, b);
		return ;
	}
	third = stack_last(*b)->prev->prev->value;
	if (first > second && first > third)
	{
		send_command("rrb", a, b);
		send_command("pa", a, b);
		send_command("rrb", a, b);
		if (second > third)
			send_command("pa", a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		if (second < third)
			send_command("pa", a, b);
	}
	if (second > first && second > third)
	{
		send_command("rrb", a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		if (first > third)
			send_command("pa", a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		if (first < third)
			send_command("pa", a, b);
	}
	if (third > second && third > first)
	{
		send_command("rrb", a, b);
		send_command("rrb", a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		if (first > second)
			send_command("sb", a, b);
		send_command("pa", a, b);
		send_command("pa", a, b);
	}
}

void	put_top_3(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

	if (!a || !b || !(*b) || amount > 3 || amount > stack_len(*b))
		return ;
	if (amount < -3 || amount < -stack_len(*b))
		return ;
	if (amount < 0)
	{
		put_top_3_rev(a, b, amount);
		return ;
	}
	if (amount > 0)
		first = (*b)->value;
	if (amount > 1)
		second = (*b)->next->value;
	if (amount > 2)
		third = (*b)->next->next->value;
	if (amount == 2 && second > first)
		send_command("sb", a, b);
	if (amount == 2)
		send_command("pa", a, b);
	if (amount == 1 || amount == 2)
		send_command("pa", a, b);
	else if (amount == 3)
	{
		first = (*b)->value;
		second = (*b)->next->value;
		third = (*b)->next->next->value;
		if (first < second && second < third) //1 2 3
		{
			send_command("sb", a, b);
			send_command("pa", a, b);
			send_command("sb", a, b);
			send_command("pa", a, b);
			send_command("sa", a, b);
			send_command("pa", a, b);
		}
		else if (second < first && first < third) // 2 1 3
		{
			send_command("pa", a, b);
			send_command("sb", a, b);
			send_command("pa", a, b);
			send_command("sa", a, b);
			send_command("pa", a, b);
		}
		else if (second < third && third < first) // 3 1 2
		{
			send_command("pa", a, b);
			send_command("sb", a, b);
			send_command("pa", a, b);
			send_command("pa", a, b);
		}
		else if (first < third && third < second) // 1 3 2
		{
			send_command("rb", a, b);
			send_command("pa", a, b);
			send_command("pa", a, b);
			send_command("rrb", a, b);
			send_command("pa", a, b);
		}
		else if (third < first && first < second) // 2 3 1
		{
			send_command("sb", a, b);
			send_command("pa", a, b);
			send_command("pa", a, b);
			send_command("pa", a, b);
		}
		else if (third < second && second < first) // 3 2 1
		{
			send_command("pa", a, b);
			send_command("pa", a, b);
			send_command("pa", a, b);
		}
	}
}

void	sort_top_3_rev(t_stack **a, t_stack **b, int amount)
{
	int	count;
	int	first;
	int	second;
	int	third;

	count = 0;
	if (amount > -3)
	{
		while (amount + count < 0)
		{
			send_command("rra", a, NULL);
			++count;
		}
		sort_top_3(a, b, count);
	}
	else if (amount == -3)
	{
		first = stack_last(*a)->prev->prev->value;
		second = stack_last(*a)->prev->value;
		third = stack_last(*a)->value;
		send_command("rra", a, b);
		if (third < first && third < second)
		{
			send_command("pb", a, b);
			send_command("rra", a, b);
			send_command("rra", a, b);
			if (second < first)
				send_command("sa", a, b);
			send_command("pa", a, b);
		}
		else if (second < first && second < third)
		{
			send_command("rra", a, b);
			send_command("pb", a, b);
			send_command("rra", a, b);
			if (first > third)
				send_command("sa", a, b);
			send_command("pa", a, b);
		}
		else
		{
			send_command("rra", a, b);
			if (second > third)
				send_command("sa", a, b);
			send_command("rra", a, b);
		}
	}
}

void	sort_top_3(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

	if (!a || !(*a) || amount > stack_len(*a) || amount > 3)
		return ;
	if (amount < 0)
	{
		sort_top_3_rev(a, b, amount);
		return ;
	}
	if (amount == 2 && (*a)->value > (*a)->next->value)
		send_command("sa", a, NULL);
	else if (amount == 3)
	{
		if (stack_len(*a) == 3)
		{
			sort_3(a, NULL);
			rotate_high_to_bottom(a);
			return ;
		}
		first = (*a)->value;
		second = (*a)->next->value;
		third = (*a)->next->next->value;
		if (first < second && second < third) //1 2 3
		{
		}
		else if (second < first && first < third) // 2 1 3
			send_command("sa", a, b);
		else if (second < third && third < first) // 3 1 2
		{
			send_command("sa", a, b);
			send_command("ra", a, b);
			send_command("sa", a, b);
			send_command("rra", a, b);
		}
		else if (first < third && third < second) // 1 3 2
		{
			send_command("ra", a, b);
			send_command("sa", a, b);
			send_command("rra", a, b);
		}
		else if (third < first && first < second) // 2 3 1
		{
			send_command("ra", a, b);
			send_command("sa", a, b);
			send_command("rra", a, b);
			send_command("sa", a, b);
		}
		else if (third < second && second < first) // 3 2 1
		{
			send_command("sa", a, b);
			send_command("ra", a, b);
			send_command("sa", a, b);
			send_command("rra", a, b);
			send_command("sa", a, b);
		}
	}
}
