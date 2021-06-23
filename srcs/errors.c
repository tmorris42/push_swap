#include "stack.h"

void	*error_and_clear(t_stack *a, t_stack *b)
{
	ft_putstr_fd("Error\n", 2);
	stack_clear(&a);
	stack_clear(&b);
	return (NULL);
}
