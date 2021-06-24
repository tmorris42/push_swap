/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 21:11:30 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/31 11:04:33 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	struct s_list	*next_fd;
	char			c;
	struct s_list	*next;
}				t_list_chr;

int				ft_lst_chr_len(t_list_chr *start);
int				ft_lst_chr_has_newline(t_list_chr *start);
void			ft_lst_chr_clear(t_list_chr **start);
t_list_chr		*ft_lst_chr_add_back(t_list_chr **start, char c, int fd);
char			*ft_lst_chr_to_str(t_list_chr **start);
int				get_next_line(int fd, char **line);

#endif
