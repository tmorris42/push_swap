/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:24:26 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/14 20:27:49 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					i;
	unsigned char		match;
	const unsigned char	*src;

	match = (unsigned char)c;
	src = (const unsigned char *)s;
	i = ft_strlen(s) + 1;
	while (--i >= 0)
		if (src[i] == match)
			return ((void *)(&src[i]));
	return (NULL);
}
