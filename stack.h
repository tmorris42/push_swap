/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:52:08 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/10 19:10:36 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft/libft.h"

typedef struct	s_stack
{
	int				value;
	struct s_stack	*next;
}				t_stack;

void			stack_clear(t_stack **stack);
t_stack			*stack_last(t_stack *stack);
void			stack_add_back(t_stack **stack, t_stack *new);
t_stack			*stack_new(int c);
int				stack_is_sorted(t_stack *stack);
void			stack_print(t_stack *a, t_stack *b);
int				stack_new_add_back(t_stack **start_addr, int value);
void			stack_add_front(t_stack **stack, t_stack *node);
void			stack_verify(t_stack *stack);
void			stack_rotate(t_stack **stack);
void			stack_push(t_stack **src, t_stack **dest);
void			stack_swap(t_stack **stack);
void			stack_reverse_rotate(t_stack **stack);

#endif
