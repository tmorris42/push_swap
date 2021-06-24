/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:42:57 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/30 22:30:23 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	int					i;

	i = 0;
	str1 = (const unsigned char *)(s1);
	str2 = (const unsigned char *)(s2);
	while (n-- > 0)
	{
		if (str1[i] != str2[i])
			return ((int)(str1[i]) - (int)(str2[i]));
		i++;
	}
	return (0);
}
