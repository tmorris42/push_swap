/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:00:41 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/11 17:35:59 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

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
	int		j;

	a = NULL;
	i = 0;
	while (i < argc)
	{
		if (!(ft_isdigits_minus(argv[i])))
		{
			ft_putstr("Error\nAll items must be integers\n"); //Only print Erri, and print to stderr
			stack_clear(&a);
			break ;
		}
		j = i + 1;
		while (j < argc)
		{
			if (ft_strncmp(argv[i], argv[j], ft_strlen(argv[i]) + 1) == 0)
			{
				ft_putstr("Error\nDuplicate value\n"); //Only print Error, and print to stderr
				stack_clear(&a);
				return (NULL);
			}
			++j;
		}
		value = ft_atoi(argv[i]);
		stack_new_add_back(&a, value); //should check for malloc error here
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
		stack = read_args_array(len, strs); //should check for malloc error here(null stack)
		strs = free_array(strs);
		return (stack);
	}
	return (read_args_array(argc - 1, &argv[1])); //should check for malloc error here (null stack)
}
