/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:52:08 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/18 14:22:42 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft/libft.h"

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
	struct s_stack	*prev;
}				t_stack;

enum	e_cmd
{
	INVALID_COMMAND = -1,
	QUIT = 0,
	SWAP_A,
	SWAP_B,
	SWAP_BOTH,
	PUSH_A,
	PUSH_B,
	ROTATE_A,
	ROTATE_B,
	ROTATE_BOTH,
	REV_ROTATE_A,
	REV_ROTATE_B,
	REV_ROTATE_BOTH
};

void			*error_and_clear(t_stack *a, t_stack *b);
int				stack_len(t_stack *stack);
void			stack_clear(t_stack **stack);
t_stack			*stack_last(t_stack *stack);
void			stack_add_back(t_stack **stack, t_stack *new);
t_stack			*stack_new(int c);
int				stack_is_sorted(t_stack *stack);
int				stack_is_ordered(t_stack *stack);
void			stack_print(t_stack *a, t_stack *b);
int				stack_new_add_back(t_stack **start_addr, int value);
void			stack_add_front(t_stack **stack, t_stack *node);
void			stack_verify(t_stack *stack, t_stack *b);
void			stack_rotate(t_stack **stack);
void			stack_push(t_stack **src, t_stack **dest);
void			stack_swap(t_stack **stack);
void			stack_reverse_rotate(t_stack **stack);
t_stack			*read_args(int argc, char **argv);
int				parse_command(char *str);
void			run_command(int cmd, t_stack **a, t_stack **b);
void			send_command(char *cmd_str, t_stack **a, t_stack **b);

#endif
