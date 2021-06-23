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
	if (amount == 2 && (*b)->next->value > (*b)->value)
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
			send_command_chain("sb pa sb pa sa pa", a, b);
		else if (second < first && first < third) // 2 1 3
			send_command_chain("pa sb pa sa pa", a, b);
		else if (second < third && third < first) // 3 1 2
			send_command_chain("pa sb pa pa", a, b);
		else if (first < third && third < second) // 1 3 2
			send_command_chain("rb pa pa rrb pa", a, b);
		else if (third < first && first < second) // 2 3 1
			send_command_chain("sb pa pa pa", a, b);
		else if (third < second && second < first) // 3 2 1
			send_command_chain("pa pa pa", a, b);
	}
}

void	sort_top_3_rev(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

	if (amount > -3)
	{
		while (amount > -3 && amount++ < 0)
			send_command("rra", a, b);
		sort_top_3(a, b, 3);
	}
	if (amount != -3)
		return ;
	first = stack_last(*a)->prev->prev->value;
	second = stack_last(*a)->prev->value;
	third = stack_last(*a)->value;
	if (third < first && third < second && second < first)
		send_command_chain("rra pb rra rra sa pa", a, b);
	else if (third < first && third < second && second > first)
		send_command_chain("rra pb rra rra pa", a, b);
	else if (second < first && second < third && first > third)
		send_command_chain("rra rra pb rra sa pa", a, b);
	else if (second < first && second < third)
		send_command_chain("rra rra pb rra pa", a, b);
	else if (second > third)
		send_command_chain("rra rra sa rra", a, b);
	else
		send_command_chain("rra rra rra", a, b);
}

void	sort_top_3(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

	if (amount < 0)
		sort_top_3_rev(a, b, amount);
	if (!a || !(*a) || amount > stack_len(*a) || amount > 3 || amount < 2)
		return ;
	if (amount == 2 && (*a)->value > (*a)->next->value)
		send_command("sa", a, b);
	if (amount != 3)
		return ;
	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (second < first && first < third)
		send_command("sa", a, b);
	else if (second < third && third < first)
		send_command_chain("sa ra sa rra", a, b);
	else if (first < third && third < second)
		send_command_chain("ra sa rra", a, b);
	else if (third < first && first < second)
		send_command_chain("ra sa rra sa", a, b);
	else if (third < second && second < first)
		send_command_chain("sa ra sa rra sa", a, b);
}
