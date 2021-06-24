/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 21:11:47 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/31 11:53:20 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_lst_split(t_list_chr **start)
{
	t_list_chr	*index;
	t_list_chr	*to_save;
	char		*str;

	to_save = NULL;
	index = *start;
	while (index && index->next && index->c != '\n')
	{
		index = index->next;
	}
	if (index)
	{
		to_save = index->next;
		index->next = NULL;
	}
	str = ft_lst_chr_to_str(start);
	*start = to_save;
	return (str);
}

static int	ft_read_file(int fd, t_list_chr **start)
{
	int			ret;
	t_list_chr	*storage;
	char		buffer[BUFFER_SIZE + 1];

	ret = 1;
	storage = (*start);
	while (ret > 0 && (ft_lst_chr_has_newline(storage) == 0))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		ret = 0;
		while (buffer[ret])
		{
			if (storage)
				storage = ft_lst_chr_add_back(&storage, buffer[ret], fd);
			else
				storage = ft_lst_chr_add_back(&(*start), buffer[ret], fd);
			if (!(storage))
				return (-1);
			ret++;
		}
	}
	return (ret);
}

static void	ft_lst_relink(t_list_chr **storage, t_list_chr *fd_link)
{
	t_list_chr	*index;

	if (!storage)
		return ;
	if (!(*storage))
	{
		(*storage) = fd_link;
		return ;
	}
	index = (*storage);
	while (index && index->next_fd)
		index = index->next_fd;
	if (index)
		index->next_fd = fd_link;
}

static t_list_chr	*ft_lst_unlink(t_list_chr **storage, int fd)
{
	t_list_chr	*index;
	t_list_chr	*next;

	if (!storage || !(*storage))
		return (NULL);
	index = (*storage);
	if (index && index->fd == fd)
	{
		*storage = index->next_fd;
		index->next_fd = NULL;
		return (index);
	}
	while (index && index->next_fd && index->next_fd->fd != fd)
		index = index->next_fd;
	if (index && index->next_fd && index->next_fd->fd == fd)
	{
		next = index->next_fd;
		index->next_fd = next->next_fd;
		next->next_fd = NULL;
		return (next);
	}
	return (index->next_fd);
}

int	get_next_line(int fd, char **line)
{
	static t_list_chr	*storage = NULL;
	int					ret;
	t_list_chr			*fd_link;

	fd_link = ft_lst_unlink(&storage, fd);
	ret = 1;
	if (BUFFER_SIZE < 1 || (!line))
		return (-1);
	ret = ft_read_file(fd, &fd_link);
	if (ret == -1)
	{
		ft_lst_chr_clear(&fd_link);
		return (-1);
	}
	ret = ft_lst_chr_has_newline(fd_link);
	*line = ft_lst_split(&fd_link);
	if (!(*line))
	{
		ft_lst_chr_clear(&fd_link);
		return (-1);
	}
	ft_lst_relink(&storage, fd_link);
	return (ret);
}
