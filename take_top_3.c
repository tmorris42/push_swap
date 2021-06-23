#include "push_swap.h"

static void	run_top_3_rev_patterns(t_stack **a, t_stack **b)
{
	int	first;
	int	second;
	int	third;

	first = stack_last(*b)->value;
	second = stack_last(*b)->prev->value;
	third = stack_last(*b)->prev->prev->value;
	if (first > second && first > third && second > third)
		send_command_chain("rrb pa rrb pa rrb pa", a, b);
	else if (first > second && first > third)
		send_command_chain("rrb pa rrb rrb pa pa", a, b);
	if (second > first && second > third && first > third)
		send_command_chain("rrb rrb pa pa rrb pa", a, b);
	else if (second > first && second > third)
		send_command_chain("rrb rrb pa rrb pa pa", a, b);
	if (third > second && third > first && first > second)
		send_command_chain("rrb rrb rrb pa sb pa pa", a, b);
	else if (third > second && third > first)
		send_command_chain("rrb rrb rrb pa pa pa", a, b);
}

void	put_top_3_rev(t_stack **a, t_stack **b, int amount)
{
	if (amount < -3 || amount > -1)
		return ;
	if (amount == -1)
	{
		send_command("rrb", a, b);
		send_command("pa", a, b);
		return ;
	}
	if (amount == -2)
	{
		if (stack_last(*b)->value > stack_last(*b)->prev->value)
			send_command_chain("rrb pa rrb pa", a, b);
		else
			send_command_chain("rrb rrb pa pa", a, b);
		return ;
	}
	run_top_3_rev_patterns(a, b);
}

static void	run_top_3_patterns(t_stack **a, t_stack **b)
{
	int	first;
	int	second;
	int	third;

	first = (*b)->value;
	second = (*b)->next->value;
	third = (*b)->next->next->value;
	if (first < second && second < third)
		send_command_chain("sb pa sb pa sa pa", a, b);
	else if (second < first && first < third)
		send_command_chain("pa sb pa sa pa", a, b);
	else if (second < third && third < first)
		send_command_chain("pa sb pa pa", a, b);
	else if (first < third && third < second)
		send_command_chain("rb pa pa rrb pa", a, b);
	else if (third < first && first < second)
		send_command_chain("sb pa pa pa", a, b);
	else if (third < second && second < first)
		send_command_chain("pa pa pa", a, b);
}

void	put_top_3(t_stack **a, t_stack **b, int amount)
{
	if (!a || !b || !(*b) || amount > 3 || amount > stack_len(*b))
		return ;
	if (amount < -3 || amount < -stack_len(*b))
		return ;
	if (amount < 0)
		put_top_3_rev(a, b, amount);
	if (amount == 2 && (*b)->next->value > (*b)->value)
		send_command("sb", a, b);
	if (amount == 2)
		send_command("pa", a, b);
	if (amount == 1 || amount == 2)
		send_command("pa", a, b);
	if (amount == 3)
		run_top_3_patterns(a, b);
}
