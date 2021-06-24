/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:20:59 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/31 10:45:28 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*results;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	results = (char *)malloc(sizeof(char) * (len + 1));
	if (!results)
		return (NULL);
	i = 0;
	while (s[i])
	{
		results[i] = (*f)(i, s[i]);
		i++;
	}
	results[i] = '\0';
	return (results);
}
