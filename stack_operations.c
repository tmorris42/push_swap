/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:57:54 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/18 14:33:52 by tmorris          ###   ########.fr       */
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
	(*stack)->prev = temp->prev;
	temp->prev = (*stack);
	temp->next->prev = temp;
}

void	stack_push(t_stack **src, t_stack **dest)
{
	t_stack	*temp;

	if (!src || !(*src))
		return ;
	temp = (*src)->next;
	stack_add_front(dest, (*src));
	(*src) = temp;
	(*src)->prev = NULL;
}

void	stack_rotate(t_stack **stack)
{
	t_stack	*last;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	last = stack_last(*stack);
	last->next = (*stack);
	last->next->prev = last;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last->next->next = NULL;
}

void	stack_reverse_rotate(t_stack **stack)
{
	t_stack *last;

	if (!stack || !(*stack))
		return ;
	last = stack_last(*stack);
	last->prev->next = NULL;
	last->prev = NULL;
	last->next = (*stack);
	last->next->prev = last;
}
