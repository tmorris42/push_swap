/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:36:49 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/31 10:54:22 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strrev(char *str)
{
	char	a;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		a = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = a;
		i++;
	}
}

static char	*ft_gen_str(char *str, int n, int sign)
{
	int		i;

	i = 0;
	if (n == 0)
	{
		str[0] = '0';
		i = 1;
	}
	while (n != 0)
	{
		str[i] = '0' + ((n % 10) *(sign));
		n = n / 10;
		i++;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*str;
	int		i;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = 1;
	i = n;
	while (i != 0)
	{
		i = i / 10;
		len++;
	}
	str = (char *)malloc(sizeof(*str) * (len + (sign == -1) + (n == 0)));
	if (!str)
		return (NULL);
	str = ft_gen_str(str, n, sign);
	ft_strrev(str);
	return (str);
}
