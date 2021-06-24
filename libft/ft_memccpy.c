/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:04:38 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/14 20:25:54 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		stop;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	stop = (unsigned char)c;
	if (!d && !s)
		return (dst);
	while (n-- > 0)
	{
		*d++ = *s++;
		if (*(d - 1) == stop)
			return (d);
	}
	return (NULL);
}
