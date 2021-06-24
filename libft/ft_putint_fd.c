/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:26:55 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/27 18:16:29 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putint_fd(int i, int fd)
{
	write(fd, &i, sizeof(i));
}

void	ft_putint(int i)
{
	ft_putint_fd(i, 1);
}
