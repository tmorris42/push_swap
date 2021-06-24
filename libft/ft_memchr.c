/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:42:35 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/14 20:26:15 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int					i;
	unsigned char		match;
	const unsigned char	*src;

	match = (unsigned char)c;
	src = (const unsigned char *)s;
	i = 0;
	while (n-- > 0)
	{
		if (src[i] == match)
			return ((void *)(&src[i]));
		i++;
	}
	return (NULL);
}
