/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:57:54 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/12 11:32:20 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int		stack_len(t_stack *stack)
{
	int		len;

	len = 0;
	while (stack)
	{
		++len;
		stack = stack->next;
	}
	return (len);
}

t_stack	*stack_new(int value)
{
	t_stack	*new;

	new = (t_stack*)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	stack_clear(t_stack **stack)
{
	t_stack	*prev;

	while (stack && *stack)
	{
		prev = *stack;
		(*stack) = (*stack)->next;
		if (prev)
			free(prev);
	}
	(*stack) = NULL;
}

t_stack	*stack_last(t_stack *stack)
{
	while (stack && stack->next)
		stack = stack->next;
	return (stack);
}

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
	}
}

void	stack_add_front(t_stack **stack, t_stack *node)
{
	if (!stack || !node)
		return ;
	node->next = *stack;
	*stack = node;
}

void	stack_print(t_stack *a, t_stack *b)
{
	while (a || b)
	{
		if (a)
		{
			ft_putnbr(a->value);
			a = a->next;
		}
		else
			ft_putstr(" ");
		ft_putchar(' ');
		if (b)
		{
			ft_putnbr(b->value);
			b = b->next;
		}
		ft_putchar('\n');
	}
	ft_putstr("_ _\na b\n");
}

int		stack_is_ordered(t_stack *stack)
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

int		stack_is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int		stack_new_add_back(t_stack **start_addr, int value)
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

void	stack_verify(t_stack *a, t_stack *b)
{
	if (b)
		ft_putstr("KO\n");
	else if (stack_is_sorted(a))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
}

void	stack_swap(t_stack **stack)
{
	t_stack	*temp;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	temp = *stack;
	(*stack) = (*stack)->next;
	temp->next = (*stack)->next;
	(*stack)->next = temp;
}

void	stack_push(t_stack **src, t_stack **dest)
{
	t_stack	*temp;

	if (!src || !(*src))
		return ;
	temp = (*src)->next;
	stack_add_front(dest, (*src));
	(*src) = temp;
}

void	stack_rotate(t_stack **stack)
{
	t_stack	*last;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	last = stack_last(*stack);
	last->next = (*stack);
	*stack = (*stack)->next;
	last->next->next = NULL;
}

void	stack_reverse_rotate(t_stack **stack)
{
	t_stack	*next;

	if (!stack || !(*stack))
		return ;
	next = ((*stack)->next);
	while (*stack && next)
	{
		if (next->next && next->next->next)
			next = next->next;
		else if (next->next)
		{
			next->next->next = (*stack);
			(*stack) = next->next;
			next->next = NULL;
			break ;
		}
		else
		{
			next->next = (*stack);
			(*stack)->next = NULL;
			(*stack) = next;
			break ;
		}
	}
}
