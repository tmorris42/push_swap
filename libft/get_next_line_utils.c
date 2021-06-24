/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 21:11:47 by tmorris           #+#    #+#             */
/*   Updated: 2021/05/14 20:48:36 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lst_chr_has_newline(t_list_chr *list)
{
	while (list)
	{
		if (list->c == '\n')
			return (1);
		list = list->next;
	}
	return (0);
}

t_list_chr	*ft_lst_chr_add_back(t_list_chr **list, char c, int fd)
{
	t_list_chr	*new_node;
	t_list_chr	*index;

	new_node = (t_list_chr *)malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->c = c;
	new_node->fd = fd;
	new_node->next_fd = NULL;
	if (!(list) || (!(*list)))
	{
		*list = new_node;
		index = new_node;
	}
	else
	{
		index = *list;
		while (index->next)
			index = index->next;
		index->next = new_node;
		index = index->next;
	}
	return (index);
}

int	ft_lst_chr_len(t_list_chr *start)
{
	int		len;

	len = 0;
	while (start)
	{
		start = start->next;
		len++;
	}
	return (len);
}

void	ft_lst_chr_clear(t_list_chr **start)
{
	t_list_chr	*index;
	t_list_chr	*next;

	if (!(start))
		return ;
	index = *start;
	while (index)
	{
		next = index->next;
		free(index);
		index = next;
	}
	*start = NULL;
}

char	*ft_lst_chr_to_str(t_list_chr **start)
{
	t_list_chr	*index;
	int			i;
	char		*str;

	i = 0;
	if (start)
		i = ft_lst_chr_len(*start);
	str = (char *)malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	if (!(start))
		return (str);
	i = 0;
	index = *start;
	while (index && index->c != '\n')
	{
		str[i] = index->c;
		i++;
		index = index->next;
	}
	str[i] = '\0';
	ft_lst_chr_clear(start);
	return (str);
}
