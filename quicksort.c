#include "push_swap.h"
#include <stdio.h> //debug only

void	insert_in_place(t_stack **a, t_stack**b);
int	quicksort_left(t_stack **a, t_stack **b, int amount);
void	rotate_high_to_bottom(t_stack **a);
void	sort_top_3(t_stack **a, t_stack **b, int amount);
int	sort_3(t_stack **a, t_stack **b);

#ifndef DEBUG
# define DEBUG 0
#endif

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

float	get_pivot_rev(t_stack *a, int limit)
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
	median = stack_last(a)->value;
	while (1)
	{
//		printf("Trying median = %f\n", median);
		lower = 0;
		higher = 0;
		i = 0;
		index = stack_last(a);
		while (index && i < limit)
		{
			if (index->value < median)
				++lower;
			if (index->value > median)
				++higher;
			index = index->prev;
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

unsigned int	pass_lowest_x_rev(t_stack **a, t_stack **b, unsigned int x)
{
	float	pivot;
	t_stack	*cursor;
	unsigned int	amt_moved;
	int	amt_skipped;

	if (DEBUG > 2)
		printf("Pass lowest rev x=%d, and sorted == %d\n", x, stack_is_sorted(*a));
	if (!a || !b)
		return (-1);
	if (x < 0)
		printf("ERROR pass_lowest_rev x is neg (== %d)\n", x);
	amt_moved = 0;
	amt_skipped = 0;
	pivot = get_pivot_rev(*a, x); //
	if (DEBUG > 2 && !stack_is_sorted(*a))
	{
		printf("Trying rev pass low with x = %d\n", x); //;
		printf("And pivot = %f\n", pivot);//
		stack_print(*a, *b);//
	}
	cursor = (*a);;
	while (cursor && amt_moved + amt_skipped < x)
	{
//		printf("And pivot = %f\n", pivot);//
		send_command("rra", a, b);
		cursor = (*a);;
		if (cursor->value <= pivot)
		{
			send_command("pb", a, b);
			++amt_moved;
		}
		else
		{
	//		send_command("rra", a, b);
			++amt_skipped;
		}
	}
	if (DEBUG > 2)
	{
		printf("Finished pass low with  x=%d, moved=%d, and sorted == %d\n", x, amt_moved, stack_is_sorted(*a));
	}
	return (amt_moved);
}

unsigned int	pass_lowest_x(t_stack **a, t_stack **b, unsigned int x)
{
	float	pivot;
	t_stack	*cursor;
	unsigned int	amt_moved;
	unsigned int	amt_skipped;

	if (DEBUG > 2)
		printf("Pass lowest x=%d, and sorted == %d\n", x, stack_is_sorted(*a));
	if (!a || !b || x > (unsigned int)stack_len(*a))
	{
		printf("ERROR x=%u and stack_len=%u\n", x, (unsigned int)stack_len(*a));
		read(0, NULL, 1);
		return (-1);
	}
	if (x < 0)
		printf("ERROR pass_lowest x is neg (== %d)\n", x);
	amt_moved = 0;
	amt_skipped = 0;
//	printf("About to go get pivot\n"); //
	pivot = get_pivot(*a, x);
	if (DEBUG > 3)
	{
		printf("And pivot = %f\n", pivot);//
	}
	cursor = (*a);
	while (cursor && amt_moved + amt_skipped < x)
	{
		cursor = (*a);
		if (cursor->value <= pivot)
		{
			send_command("pb", a, b);
			++amt_moved;
		}
		else
		{
			send_command("ra", a, b);
			++amt_skipped;
		}
	}
	if (DEBUG > 2)
	{
		printf("Finished pass low with  x=%d, moved=%d, and sorted == %d\n", x, amt_moved, stack_is_sorted(*a));
	}
	return (amt_moved);
}

int	take_highest_x_rev(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack	*cursor;
	int	amt_moved;
	int	amt_skipped;

	if (DEBUG > 2)
		printf("Take highest rev x=%d, and sorted == %d\n", x, stack_is_sorted(*a));
	if (!a || !b)
		return (-1);
	if (x < 0)
		printf("ERROR take_highest x is neg\n"); //
	if (x == 1)
	{
		send_command("rrb", a, b);
		send_command("pa", a, b);
		return (1);
	}
	amt_moved = 0;
	amt_skipped = 0;
	if (x > stack_len(*b))
		x = stack_len(*b);
	pivot = get_pivot_rev(*b, x); //
	while (x < 3 && amt_moved < x)
	{
		insert_in_place(a, b);
		send_command("rrb", a, b);
		send_command("pa", a, b);
		++amt_moved;
	}
	if (x < 4)
		return (amt_moved);
	cursor = (*b);
	while (cursor && amt_skipped + amt_moved < x)
	{
		send_command("rrb", a, b);
		cursor = (*b);
		if (cursor->value > pivot)
		{
			send_command("pa", a, b);
			++amt_moved;
		}
		else
		{
			++amt_skipped;
//			stack_print(*a, *b);
//			printf("amt_skipped = %d, x = %d, pivot = %d, value=%d\n", amt_skipped, x, pivot, (*b)->value); //DEL
		}
	}
	if (DEBUG > 2)
		printf("Finished take highest rev x=%d, moved=%d, and sorted == %d\n", x, amt_moved, stack_is_sorted(*a));
	return (amt_moved);
}

int	take_highest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack	*cursor;
	int	amt_moved;
	int	amt_skipped;

	if (DEBUG > 2)
		printf("Take highest x=%d, and sorted == %d\n", x, stack_is_sorted(*a));
	if (!a || !b)
		return (-1);
	if (x < 0)
		printf("ERROR take_highest x is neg\n"); //
	if (x == 1)
	{
		send_command("pa", a, b);
		return (0);
	}
	amt_moved = 0;
	amt_skipped = 0;
	if (x > stack_len(*b))
		x = stack_len(*b);
	pivot = get_pivot(*b, x); //
	while (x < 3 && amt_moved < x)
	{
//		insert_in_place(a, b);
		send_command("pa", a, b);
		++amt_moved;
	}
	if (x < 4)
		return (amt_moved);
	cursor = (*b);
	while (cursor && (amt_skipped + amt_moved < x))
	{
		cursor = (*b);
		if (cursor->value > pivot)
		{
			send_command("pa", a, b);
			++amt_moved;
		}
		else
		{
			send_command("rb", a, b);
			++amt_skipped;
		}
	}
	if (DEBUG > 2)
		printf("Finished take highest x=%d, moved=%d, and sorted == %d\n", x, amt_moved, stack_is_sorted(*a));
	return (amt_moved);
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
	first = 0;
	while (amount + first < 0) //can be sorted as it is pulled down to save steps
	{
		send_command("rrb", a, b);
		++first;
	}
	if (amount < 0)
		amount *= -1;
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
/*		if (first > second)
			send_command("sa", a, NULL);
		if (first > second && third > first)
			return ;
		send_command("ra", a, NULL);
		send_command("sa", a, NULL);
		send_command("rra", a, NULL);
		if (first > third && second > first)
			send_command("sa", a, NULL);
		if (first > second && second > third)
			send_command("sa", a, NULL); */
//		first = (*a)->value; //
//		second = (*a)->next->value; //
//		third = (*a)->next->next->value; //
//		if (first > second || second > third || first > third) //
//		{//
//			printf("ERROR not sorted after top 3\n"); //
//			stack_print(*a, NULL);//
//		}//
	}
//	first = (*a)->value;  //
//	second = (*a)->next->value; //
//	third = (*a)->next->next->value; //
//	printf("a: %d %d %d ... %d\n", first, second, third, stack_last(*a)->value); //
//	if (!stack_is_sorted(*a)) //
//	{ //
//		printf("print the stack\n"); //
//		stack_print(*a, NULL); //
//		exit(0); //
//	}
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
		sort_top_3(a, b, amount);
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
