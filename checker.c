/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:31:09 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/12 16:26:15 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "checker.h"

int	get_commands(t_stack **a, t_stack **b)
{
	char		*buf;
	int			status;
	enum e_cmd	cmd;

	buf = NULL;
	status = 1;
	while (status > 0)
	{
		status = get_next_line(0, &buf);
		if (status > 0)
		{
			cmd = parse_command(buf);
			if (cmd > 0)
				run_command(cmd, a, b);
			else
			{
				free(buf);
				ft_putstr_fd("Error\n", 2);
				return (-1);
			}
		}
		free(buf);
		buf = NULL;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	b = NULL;
	a = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (0);
	if (!get_commands(&a, &b))
		stack_verify(a, b);
	stack_clear(&a);
	stack_clear(&b);
	return (0);
}
