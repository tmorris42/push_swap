/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:56:43 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/11 16:33:40 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rough_sort(t_stack **a, t_stack **b)
{
	int		len_a;
	int		sorted;

	len_a = stack_len(*a);
	if (len_a < 2)
		return ;
	sorted = ((stack_is_sorted(*a)) && ((*b) == NULL));
	while (!sorted)
	{
		if ((*a) && !stack_is_sorted(*a))
		{
			if ((*a)->value < (*a)->next->value)
			{
				if (!(*b) || ((*b)->value < (*a)->value))
				{
					ft_putstr("pb\n");
					stack_push(a, b);
				}
				else
				{
					ft_putstr("pa\n");
					stack_push(b, a);
				}
			}
			else
			{
				ft_putstr("sa\n");
				stack_swap(a);
			}
		}
		else
		{
			ft_putstr("pa\n");
			stack_push(b, a);
		}
		sorted = ((stack_is_sorted(*a)) && ((*b) == NULL));
	}
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack *b;

	b = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (-1);
	rough_sort(&a, &b);
	return (0);
}
