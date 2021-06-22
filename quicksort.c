#include "push_swap.h"
#include <stdio.h> //debug only

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
