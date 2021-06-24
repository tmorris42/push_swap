/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:54:28 by tmorris           #+#    #+#             */
/*   Updated: 2021/06/21 15:13:31 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_abs(int a)
{
	unsigned int	result;

	if (a < 0)
		result = (unsigned int)(a * -1);
	else
		result = (unsigned int)a;
	return (result);
}
