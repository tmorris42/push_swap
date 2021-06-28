#include "stack.h"

int	ft_isdigits_or(char *str, char *extra)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit(str[i])))
		{
			j = ft_strlen(extra) - 1;
			while (j > -1 && extra)
			{
				if (str[i] == extra[j])
					break ;
				--j;
			}
			if (j < 0)
				return (0);
		}
		++i;
	}
	return (1);
}

t_stack	*read_args_array(int argc, char **argv)
{
	int		i;
	t_stack	*a;
	int		value;
	t_stack	*index;

	a = NULL;
	i = 0;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		if (!(ft_isdigits_or(argv[i], "-")) || (value != (int)ft_atol(argv[i])))
			return (error_and_clear(a, NULL));
		index = a;
		while (index)
		{
			if (index->value == value)
				return (error_and_clear(a, NULL));
			index = index->next;
		}
		if (stack_new_add_back(&a, value) == -1)
			return (error_and_clear(a, NULL));
		++i;
	}
	return (a);
}

int	get_array_len(char **strs)
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

	if (argc == 2 && ft_isdigits_or(argv[1], "- "))
	{
		strs = ft_split(argv[1], ' ');
		if (!strs)
			return (NULL);
		len = get_array_len(strs);
		stack = read_args_array(len, strs);
		strs = free_array(strs);
		if (len < 1)
			return (error_and_clear(stack, NULL));
		return (stack);
	}
	return (read_args_array(argc - 1, &argv[1]));
}
