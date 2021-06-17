#include "push_swap.h"
#include <stdio.h> //debug only

void	insert_in_place(t_stack **a, t_stack**b);
int	quicksort_left(t_stack **a, t_stack **b, int amount);
void	rotate_high_to_bottom(t_stack **a);
int	sort_3(t_stack **a, t_stack **b);

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

/*int	quicksort_iter(t_stack **a, t_stack **b)
{
	float pivot;
	int	limit;
	int	i;
	int	amt_skipped;
	int	amt_sorted;

	if (!a || !b)
		return (-1);
	amt_sorted = 0;
	while (!stack_is_ordered(*a)) //|| stack_len(*b))
	{
		limit = stack_len(*a) - amt_sorted;
		pivot = get_pivot(*a, limit);
		printf("Pivot = %f\n", pivot);
		i = 0;
		amt_skipped = 0;
		while (i < limit)
		{
			if ((*a)->value < pivot)
			{
				send_command("pb", a,b);
			}
			else
			{
				send_command("ra", a, b);
				++amt_skipped;
			}
			++i;
		}
		while (amt_sorted && amt_skipped)
		{
			send_command("rra", a, b);
			--amt_skipped;
		}
	}
	if (stack_len(*b))
	{
		take_from_b(a, b);
		// start over
	}
	return (0);
}*/

int	pass_lowest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack *stop;
	t_stack	*cursor;
	t_stack	*next;
	int	amt_moved;
	int	amt_skipped;

	if (!a || !b)
		return (-1);
	if (x < 0)
		printf("ERROR pass_lowest x is neg\n");
	amt_moved = 0;
	amt_skipped = 0;
	stop = NULL;
	pivot = get_pivot(*a, x); //
	//printf("Pivot = %d\n", pivot);
	cursor = (*a);
	while (cursor && amt_moved + amt_skipped < x)
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
		{
			send_command("ra", a, b);
			++amt_skipped;
		}
		cursor = next;
		if (cursor == stop)
			return (amt_moved);
	}
	while (amt_skipped > 0)
	{
		send_command("rra", a, b);
		--amt_skipped;
	}
	return (amt_moved);
}

int	take_highest_x(t_stack **a, t_stack **b, int x)
{
	float	pivot;
	t_stack	*cursor;
	int	amt_moved;
	int	amt_skipped;

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
		send_command("sa", a, b);
		++amt_moved;
	}
	if (x < 4)
		return (amt_moved);
//	if (x == 5)//
//	{//
//		printf("x=%d, pivot=%f\n", x, pivot);//
//		stack_print(*a, *b); //
//	}//
	cursor = (*b);
	while (cursor && (amt_skipped + amt_moved < x && 2 * amt_moved <= x))
	{
		cursor = (*b);
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
	while (amt_skipped > 0)
	{
		send_command("rrb", a, b);
		--amt_skipped;
	}
	return (amt_moved);
}

void put_top_3(t_stack **a, t_stack **b, int amount)
{
	int	first;
	int	second;
	int	third;

//	printf("put top 3!!\n"); //
	if (!a || !b || !(*b) || amount > 3 || amount > stack_len(*b))
		return ;
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
			stack_print(*a, NULL);//
		}//
	}

}

int	quicksort_right(t_stack **a, t_stack **b, int amount)
{
	int	amt_moved;

	amt_moved = 0;
	if (amount < 1 || !stack_len(*b))
		return (0);
	if (amount < 4)
	{
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
		amt_moved = take_highest_x(a, b, amount);
		if (amt_moved == amount) //
			printf ("ERROR, moved whole stack\n"); //
		if (amt_moved > amount) //
			printf("ERROR, moved more than whole stack\n"); //
		//move from right to left (amount / 2))
		//	remember that if amount < 0: cmd = "rrb" else "rb"
		quicksort_left(a, b, amt_moved);
		quicksort_right(a, b, amount - amt_moved);
	}
	return (amt_moved);
}

void	sort_top_3(t_stack **a, int amount)
{
	int	first;
	int	second;
	int	third;
	t_stack **b; //

	b = NULL; //

	if (!a || !(*a) || amount < 2 || amount > stack_len(*a))
		return ;
	if (amount > 3)
		printf("ERROR, MORE THAN 3 PUT AT SORT TOP THREE\n");//
	if (amount == 2)
		send_command("sa", a, NULL);
	else if (amount == 3)
	{
		if (stack_len(*a) == 3)
		{
			sort_3(a, NULL);
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
		first = (*a)->value; //
		second = (*a)->next->value; //
		third = (*a)->next->next->value; //
		if (first > second || second > third || first > third) //
		{//
			printf("ERROR not sorted after top 3\n"); //
			stack_print(*a, NULL);//
		}//
	}
}

int	quicksort_left(t_stack **a, t_stack **b, int amount)
{
	int	amt_moved;

	amt_moved = 0;
	if (stack_is_sorted(*a) || amount == 0)
		return (0);
	if (amount > -3 && amount < 4)
	{
		//swap the top two, or pull down and swap the top two
//		if (amount < 0)
//			send_command("rra", a, b);
//		send_command("sa", a, b);
		sort_top_3(a, amount);
	}
	else
	{
		amt_moved = pass_lowest_x(a, b, amount);
		if (amt_moved == amount) //
			printf ("ERROR, moved whole stack from left to right\n"); //
		//move from left to right (amount - (amount / 2))
		//	remember that if amount < 0: cmd = "rra" else "ra"
		quicksort_left(a, b, amount - amt_moved);
//		printf("amt_moved == %d, stack_len(a) == %d\n", amt_moved, stack_len(*a));
//		stack_print(*a, *b);
//		exit(0); //TESTING
		quicksort_right(a, b, amt_moved);
	}
	return (0);
}

int	quicksort_recursive(t_stack **a, t_stack **b)
{
	quicksort_left(a, b, stack_len(*a));
	return (0);
}

int	quicksort(t_stack **a, t_stack **b)
{
	return (quicksort_recursive(a, b));
}
