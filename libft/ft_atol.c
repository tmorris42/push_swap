#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long long int	ft_atol(const char *str)
{
	long long int	value;
	int				sign;
	int				i;

	value = 0;
	sign = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		value = value * 10;
		value += (sign * (str[i] - '0'));
		i++;
	}
	if ((value > 0 && sign == -1) || (value < 0 && sign == 1))
		return (0);
	return (value);
}
