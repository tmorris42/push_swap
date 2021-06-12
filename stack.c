/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:57:54 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/12 16:46:41 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	stack_len(t_stack *stack)
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

	new = (t_stack *)malloc(sizeof(*new));
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
