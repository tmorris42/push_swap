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

void	get_commands(t_stack **a, t_stack **b)
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
			if (cmd)
				run_command(cmd, a, b);
			else
				status = -1;
		}
		free(buf);
		buf = NULL;
	}
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
	get_commands(&a, &b);
	stack_verify(a, b);
	stack_clear(&a);
	return (0);
}
