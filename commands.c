/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:23:11 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/23 14:15:24 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

enum e_cmd	parse_command(char *str)
{
	if (!ft_strncmp(str, "sa", 3))
		return (SWAP_A);
	if (!ft_strncmp(str, "sb", 3))
		return (SWAP_B);
	if (!ft_strncmp(str, "ss", 3))
		return (SWAP_BOTH);
	if (!ft_strncmp(str, "pa", 3))
		return (PUSH_A);
	if (!ft_strncmp(str, "pb", 3))
		return (PUSH_B);
	if (!ft_strncmp(str, "ra", 3))
		return (ROTATE_A);
	if (!ft_strncmp(str, "rb", 3))
		return (ROTATE_B);
	if (!ft_strncmp(str, "rr", 3))
		return (ROTATE_BOTH);
	if (!ft_strncmp(str, "rra", 4))
		return (REV_ROTATE_A);
	if (!ft_strncmp(str, "rrb", 4))
		return (REV_ROTATE_B);
	if (!ft_strncmp(str, "rrr", 4))
		return (REV_ROTATE_BOTH);
	return (INVALID_COMMAND);
}

void	run_command(enum e_cmd cmd, t_stack **a, t_stack **b)
{
	if (cmd == SWAP_A || cmd == SWAP_BOTH)
		stack_swap(a);
	if (cmd == SWAP_B || cmd == SWAP_BOTH)
		stack_swap(b);
	if (cmd == PUSH_A)
		stack_push(b, a);
	if (cmd == PUSH_B)
		stack_push(a, b);
	if (cmd == ROTATE_A || cmd == ROTATE_BOTH)
		stack_rotate(a);
	if (cmd == ROTATE_B || cmd == ROTATE_BOTH)
		stack_rotate(b);
	if (cmd == REV_ROTATE_A || cmd == REV_ROTATE_BOTH)
		stack_reverse_rotate(a);
	if (cmd == REV_ROTATE_B || cmd == REV_ROTATE_BOTH)
		stack_reverse_rotate(b);
	if (cmd == INVALID_COMMAND)
		cmd = QUIT;
}

void	send_command(char *cmd_str, t_stack **a, t_stack **b)
{
	enum e_cmd	cmd;

	cmd = parse_command(cmd_str);
	if (cmd != INVALID_COMMAND)
	{
		ft_putstr(cmd_str);
		ft_putchar('\n');
		run_command(cmd, a, b);
	}
}

void	send_command_chain(char *cmds, t_stack **a, t_stack **b)
{
	char	cmd[4];
	int		i;

	i = 0;
	while (cmds && i < 4)
	{
		if (cmds[i] == ' ' || cmds[i] == '\0')
		{
			cmd[i] = '\0';
			send_command(cmd, a, b);
			if (cmds[i])
				send_command_chain(&cmds[i + 1], a, b);
		}
		else
			cmd[i] = cmds[i];
		++i;
	}
}
