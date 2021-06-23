#include "push_swap.h"

void	lowhigh_prev_x(t_stack *stack, int x, int pivot, int *lowhigh)
{
	int	low;
	int	high;
	int	i;

	i = 0;
	low = pivot - 1;
	high = pivot - 1;
	stack = stack_last(stack);
	while (stack && i < x)
	{
		if (stack->value > pivot && (stack->value < low || low < pivot))
			low = stack->value;
		if (stack->value > pivot && (stack->value > high))
			high = stack->value;
		stack = stack->prev;
		++i;
	}
	lowhigh[0] = low;
	lowhigh[1] = high;
}

void	lowhigh_next_x(t_stack *stack, int x, int pivot, int *lowhigh)
{
	int	low;
	int	high;
	int	i;

	i = 0;
	low = pivot - 1;
	high = pivot - 1;
	while (stack && i < x)
	{
		if (stack->value > pivot && (stack->value < low || low < pivot))
			low = stack->value;
		if (stack->value > pivot && (stack->value > high))
			high = stack->value;
		stack = stack->next;
		++i;
	}
	lowhigh[0] = low;
	lowhigh[1] = high;
}
