#include "push_swap.h"
#include <stdio.h> //debug only

void put_top_3_rev(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

	if (DEBUG > 2)
	{
		printf("PUT TOP 3 REV: amount=%d\n", amount);
		stack_print(*a, *b);
	}
	if (amount < -3 || amount > -1)
	{
		printf("ERROR\n"); //
	}
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
		if (DEBUG > 2)
		{
			printf("FINISHED PUT TOP 3 REV: amount=%d\n", amount);
			stack_print(*a, *b);
		}
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
	if (DEBUG > 2)
	{
		printf("FINISHED PUT TOP 3 REV: amount=%d\n", amount);
		stack_print(*a, *b);
	}
}

void put_top_3(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

//	printf("putting top 3 and sorted == %d\n", stack_is_sorted(*a));
	if (!a || !b || !(*b) || amount > 3 || amount > stack_len(*b))
		return ;
	if (amount < -3 || amount < -stack_len(*b))
		return ;
	if (amount < 0)
	{
		put_top_3_rev(a, b, amount);
		return ;
	}
//	first = 0;
//	while (amount + first < 0) //can be sorted as it is pulled down to save steps
//	{
//		if (DEBUG > 2)
//			printf("REWINDING 1\n");
//		send_command("rrb", a, b);
//		++first;
//	}
//	if (amount < 0)
//		amount *= -1;
	if (amount > 3)
		printf("ERROR, MORE THAN 3 PUT AT SORT TOP THREE\n");//
	if (amount > 0)
		first = (*b)->value;
	if (amount > 1)
		second = (*b)->next->value;
	if (amount > 2)
		third = (*b)->next->next->value;
	if (amount == 2 && second > first )
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
		first = (*a)->value; //
		second = (*a)->next->value; //
		third = (*a)->next->next->value; //
		if (first > second || second > third || first > third) //
		{//
			printf("ERROR not sorted after top 3 PLACED\n"); //
//			stack_print(*a, NULL);//
		}//
	}
//	printf("Finished putting top 3 and sorted == %d\n", stack_is_sorted(*a));
	if (!stack_is_sorted(*a))
	{
//		printf("ERROR not sorted after top 3 PLACED\n"); //
//		read(0, NULL, 1);
	}
}

int	quicksort_right(t_stack **a, t_stack **b, int amount)
{
	unsigned int	amt_moved;

//	printf("Quicksorting_right, amount=%d, and sorted == %d\n", amount, stack_is_sorted(*a));
//	if (1 || !stack_is_sorted(*a)) //
//	{ //
//		printf("print the stack\n"); //
//		stack_print(*a, *b); //
//	}
	amt_moved = 0;
	if (amount == 0 || !stack_len(*b))
		return (0);
	if (amount > -4 && amount < 4)
	{
//		if (amount < 0)
//			printf("WARNING, does put_top_3 really work with amount <0 ==%d\n", amount);
		put_top_3(a, b, amount);
//		while (amt_moved < amount)
//		{
//			send_command("pa", a, b);
//			insert_in_place(a, b);
//			++amt_moved;
//		}
//		quicksort_left(a, b, amt_moved);
	}
	else if (amount > 0 && amount < 7)
	{
		while (amt_moved < ft_abs(amount))
		{
			insert_in_place(a, b);
			++amt_moved;
		}
		rotate_high_to_bottom(a);
	}
	else
	{
		if (amount > 0)
			amt_moved = take_highest_x(a, b, ft_abs(amount));
		else
			amt_moved = take_highest_x_rev(a, b, ft_abs(amount));
		if (amt_moved == ft_abs(amount)) //
			printf ("ERROR, moved whole stack\n"); //
		if (amt_moved > ft_abs(amount)) //
			printf("ERROR, moved more than whole stack\n"); //
		//move from right to left (amount / 2))
		//	remember that if amount < 0: cmd = "rrb" else "rb"
		quicksort_left(a, b, (int)amt_moved);
		if (amount < 0)
			quicksort_right(a, b, (int)(ft_abs(amount) - amt_moved));
		else
			quicksort_right(a, b, (-1) * (int)(amount - amt_moved));
	}
	if (DEBUG > 2)
		printf("Finished quicksort_right amount=%d, and sorted == %d\n", amount, stack_is_sorted(*a));
	return (amt_moved);
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

	if (!a || !(*a) || amount > stack_len(*a))
		return ;
//	first = 0;
//	while (amount + first < 0)
//	{
//		send_command("rra", a, NULL);
//		++first;
//	}
	if (amount < 0)
	{
		sort_top_3_rev(a, b, amount);
		return ;
	}
//		amount *= -1;
	if (amount > 3)
		printf("ERROR, MORE THAN 3 PUT AT SORT TOP THREE\n");//
//	first = (*a)->value;  //
//	second = (*a)->next->value; //
//	third = (*a)->next->next->value; //
//	printf("a: %d %d %d ... %d\n", first, second, third, stack_last(*a)->value); //
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

int	quicksort_left(t_stack **a, t_stack **b, int amount)
{
	unsigned int	amt_moved;

	if (DEBUG > 2)
		printf("Quicksorting_left, amount=%d, and sorted == %d\n", amount, stack_is_sorted(*a));
//	if (1 || !stack_is_sorted(*a)) //
//	{ //
//		printf("print the stack\n"); //
//		stack_print(*a, *b); //
//	}
	amt_moved = 0;
	if (stack_is_sorted(*a) || amount == 0)
		return (0);
	if (amount > -4 && amount < 4)
	{
		if (stack_len(*a) < 4)
		{
			sort_3(a, b);
			rotate_high_to_bottom(a);
		}
		else
			sort_top_3(a, b, amount);
	}
	else if (amount > -6 && amount < 6 && stack_len(*a) < 6)
	{
		sort_5(a, b);
		rotate_high_to_bottom(a);
	}
	else if ((amount == -6 || amount == 6) && stack_len(*a) == 6)
	{
		if (DEBUG > 2)
		{
			stack_print(*a, *b);
			read(0, NULL, 1);
		}
		send_command("pb", a, b);
		sort_5(a, b);
		insert_in_place(a, b);
		rotate_high_to_bottom(a);
		if (DEBUG > 2)
		{
			stack_print(*a, *b);
			read(0, NULL, 1);
		}
	}
	else if (amount == stack_len(*a) && stack_len(*b) == 0)
	{
		amt_moved = pass_lowest_x_double(a, b, (unsigned int)ft_abs(amount));
		quicksort_left(a, b, (-1) * (amount - amt_moved));
		quicksort_right(a, b, (amt_moved / 2) + (amt_moved % 2));
		quicksort_right(a, b, (amt_moved / 2));
//		quicksort_right(a, b, (amt_moved / 2) + (amt_moved % 2));
	}
	else
	{
		if (amount > 0 || ft_abs(amount) == (unsigned int)stack_len(*a))
		{
//			printf("proceeding with lowest forward amount = %d\n", amount);
			amt_moved = pass_lowest_x(a, b, (unsigned int)ft_abs(amount));
		}
		else
		{
//			printf("proceeding with lowest reverse amount = %d\n", amount);
			amt_moved = pass_lowest_x_rev(a, b, ft_abs(amount));
		}
		if (ft_abs(amt_moved) == ft_abs(amount)) //
			printf ("ERROR, moved whole stack from left to right\n"); //
		//move from left to right (amount - (amount / 2))
		//	remember that if amount < 0: cmd = "rra" else "ra"
		if (amount < 0)
		{
			quicksort_left(a, b, ft_abs(amount) - amt_moved);
//		printf("amt_moved == %d, stack_len(a) == %d\n", amt_moved, stack_len(*a));
//		stack_print(*a, *b);
//		exit(0); //TESTING
			quicksort_right(a, b, amt_moved);
		}
		else
		{
			quicksort_left(a, b, (-1) * (amount - amt_moved));
			quicksort_right(a, b, amt_moved);
		}
	}
	if (DEBUG > 2)
		printf("Finished quicksort_left amount=%d,  nd sorted == %d\n", amount, stack_is_sorted(*a));
	return (0);
}

int	quicksort_recursive(t_stack **a, t_stack **b)
{
	quicksort_left(a, b, stack_len(*a));
	if (DEBUG > 2)
		stack_print(*a, *b);
	return (0);
}

int	quicksort(t_stack **a, t_stack **b)
{
	return (quicksort_recursive(a, b));
}
