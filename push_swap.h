#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stack.h"

float			get_pivot(t_stack *a, int limit, float guess);
float			get_upper_pivot(t_stack *a, float pivot, float guess);
float			get_pivot_rev(t_stack *a, int limit, float guess);
void			lowhigh_prev_x(t_stack *stack, int x, int pivot, int *lowhigh);
void			lowhigh_next_x(t_stack *stack, int x, int pivot, int *lowhigh);
unsigned int	push_lowest_x_rev(t_stack **a, t_stack **b, unsigned int x);
unsigned int	push_lowest_x_double(t_stack **a, t_stack **b, unsigned int x);
unsigned int	push_lowest_x(t_stack **a, t_stack **b, unsigned int x);
int				take_highest_x_rev(t_stack **a, t_stack **b, int x);
int				take_highest_x(t_stack **a, t_stack **b, int x);
void			insert_in_place(t_stack **a, t_stack**b);
int				quicksort_left(t_stack **a, t_stack **b, int amount);
void			rotate_high_to_bottom(t_stack **a);
void			sort_top_3(t_stack **a, t_stack **b, int amount);
int				sort_3(t_stack **a, t_stack **b);
int				sort_5(t_stack **a, t_stack **b);
void			put_top_3(t_stack **a, t_stack **b, int amount);
int				quicksort(t_stack **a, t_stack **b);

#endif
