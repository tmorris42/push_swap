#include "push_swap.h"

int	sort_5(t_stack **a, t_stack **b)
{
	send_command("pb", a, b);
	send_command("pb", a, b);
	sort_3(a, b);
	insert_in_place(a, b);
	insert_in_place(a, b);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		len;

	b = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (0);
//	send_command_chain("ra sa rra sa", &a, &b); //
//	exit(0);
	len = stack_len(a);
	if (len < 4)
		sort_3(&a, &b);
	else if (len < 6)
		sort_5(&a, &b);
	else
		quicksort(&a, &b);
	rotate_high_to_bottom(&a);
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
