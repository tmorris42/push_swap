/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:31:09 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/08 19:33:43 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "checker.h"

int		ft_isdigits_minus(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit(str[i])) && str[i] != '-')
			return (0);
		++i;
	}
	return (1);
}

t_stack	*read_args(int argc, char **argv)
{
	int		i;
	t_stack	*a;
	int		value;

	a = NULL;
	i = 1;
	while (i < argc)
	{
		if (!(ft_isdigits_minus(argv[i])))
		{
			ft_putstr("All items must be integers\n");
			stack_clear(&a);
			break;
		}
		value = ft_atoi(argv[i]);
		stack_new_add_back(&a, value);
		++i;
	}
	return (a);
}

void	verify_stack(t_stack *a)
{
	if (stack_is_sorted(a))
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

	if (!src || !(*src) || !dest)
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
			break;
		}
		else
		{
			next->next = (*stack);
			(*stack)->next = NULL;
			(*stack) = next;
			break;
		}
	}
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack *b;

	b = NULL;
	a = NULL;
	a = read_args(argc, argv);
	stack_print(a, b);	
	verify_stack(a);
	ft_putstr("\n\n");
	stack_rotate(&a);
	stack_print(a, b);	
	verify_stack(a);
	stack_clear(&a);
	return (0);
}
