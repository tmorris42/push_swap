#include "stack.h"

void	stack_add_back(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	if (!stack)
		return ;
	if (!(*stack))
		(*stack) = new;
	else
	{
		last = stack_last(*stack);
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
}

void	stack_add_front(t_stack **stack, t_stack *node)
{
	if (!stack || !node)
		return ;
	node->next = *stack;
	node->prev = NULL;
	*stack = node;
	if (node->next)
		node->next->prev = node;
}

int	stack_is_ordered(t_stack *stack)
{
	int		first_value;
	int		trip_count;

	if (!stack)
		return (1);
	first_value = stack->value;
	trip_count = 0;
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
		{
			if (trip_count > 0)
				return (0);
			++trip_count;
		}
		stack = stack->next;
	}
	if (trip_count == 1)
	{
		if (stack->value > first_value)
			return (0);
	}
	return (1);
}

int	stack_is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	stack_new_add_back(t_stack **start_addr, int value)
{
	t_stack	*new;

	new = stack_new(value);
	if (!new)
	{
		stack_clear(start_addr);
		return (-1);
	}
	stack_add_back(start_addr, new);
	return (0);
}
