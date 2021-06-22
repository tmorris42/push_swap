/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:03:46 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/22 18:02:18 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stack.h"

#ifndef DEBUG
# define DEBUG 0
#endif

float	get_pivot(t_stack *a, int limit);
float	get_upper_pivot(t_stack *a, float pivot);
float	get_pivot_rev(t_stack *a, int limit);
void	lowhigh_prev_x(t_stack *stack, int x, int pivot, int *lowhigh);
void	lowhigh_next_x(t_stack *stack, int x, int pivot, int *lowhigh);
unsigned int	pass_lowest_x_rev(t_stack **a, t_stack **b, unsigned int x);
unsigned int	pass_lowest_x_double(t_stack **a, t_stack **b, unsigned int x);
unsigned int	pass_lowest_x(t_stack **a, t_stack **b, unsigned int x);

#endif
