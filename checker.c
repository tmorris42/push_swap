/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:31:09 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/10 19:15:49 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "checker.h"

enum e_cmd{INVALID_COMMAND = -1, QUIT = 0, SWAP_A, SWAP_B, SWAP_BOTH, \
	PUSH_A, PUSH_B, ROTATE_A, ROTATE_B, ROTATE_BOTH, REV_ROTATE_A, \
		REV_ROTATE_B, REV_ROTATE_BOTH};

int		ft_isdigits_minus(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit(str[i])) && str[i] != '-')
			return (0);
		++i;
	}
	return (1);
}

int		ft_isdigits_minus_space(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit(str[i])) && str[i] != '-' && str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

t_stack	*read_args_array(int argc, char **argv)
{
	int		i;
	t_stack	*a;
	int		value;

	a = NULL;
	i = 0;
	while (i < argc)
	{
		if (!(ft_isdigits_minus(argv[i])))
		{
			ft_putstr("All items must be integers\n");
			stack_clear(&a);
			break ;
		}
		value = ft_atoi(argv[i]);
		stack_new_add_back(&a, value);
		++i;
	}
	return (a);
}

int		get_array_len(char **strs)
{
	int		i;

	i = 0;
	while (strs && strs[i])
		++i;
	return (i);
}

char	**free_array(char **strs)
{
	int		i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		++i;
	}
	free(strs);
	return (NULL);
}

t_stack	*read_args(int argc, char **argv)
{
	char	**strs;
	int		len;
	t_stack	*stack;

	if (argc == 2 && ft_isdigits_minus_space(argv[1]))
	{
		strs = ft_split(argv[1], ' ');
		if (!strs)
			return (NULL);
		len = get_array_len(strs);
		stack = read_args_array(len, strs);
		strs = free_array(strs);
		return (stack);
	}
	return (read_args_array(argc - 1, &argv[1]));
}

int		parse_command(char *str)
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
	if (!ft_strncmp(str, "rra", 3))
		return (REV_ROTATE_A);
	if (!ft_strncmp(str, "rrb", 3))
		return (REV_ROTATE_B);
	if (!ft_strncmp(str, "rrr", 3))
		return (REV_ROTATE_BOTH);
	else
		return (INVALID_COMMAND);
	
}

void	run_command(int cmd, t_stack **a, t_stack **b)
{
	if (cmd == SWAP_A)
		stack_swap(a);
	else if (cmd == SWAP_B)
		stack_swap(b);
	else if (cmd == SWAP_BOTH)
	{
		stack_swap(a);
		stack_swap(b);
	}
	else if (cmd == PUSH_A)
		stack_push(b, a);
	else if (cmd == PUSH_B)
		stack_push(a, b);
	else if (cmd == ROTATE_A)
		stack_rotate(a);
	else if (cmd == ROTATE_B)
		stack_rotate(b);
	else if (cmd == ROTATE_BOTH)
	{
		stack_rotate(a);
		stack_rotate(b);
	}
	else if (cmd == REV_ROTATE_A)
		stack_reverse_rotate(a);
	else if (cmd == REV_ROTATE_B)
		stack_reverse_rotate(b);
	else if (cmd == REV_ROTATE_BOTH)
	{
		stack_reverse_rotate(a);
		stack_reverse_rotate(b);
	}
}

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
			run_command(cmd, a, b);
			ft_putstr("\nCommand: ");
			ft_putnbr(cmd);
			ft_putstr("\nStatus: ");
			ft_putnbr(status);
			ft_putstr("\nHere is the line: ");
			ft_putstr(buf);
			ft_putstr("\n");
			stack_print(*a, *b);
		}
		free(buf);
		buf = NULL;
	}
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack *b;

	b = NULL;
	a = NULL;
	a = read_args(argc, argv);
	if (!a)
		return (0);
	stack_print(a, b);
	
	get_commands(&a, &b);
	
	stack_verify(a);
	stack_clear(&a);
	return (0);
}
