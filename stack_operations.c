/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:57:54 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/12 16:45:20 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

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
