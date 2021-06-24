/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorris <tmorris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:59:36 by tmorris           #+#    #+#             */
/*   Updated: 2020/12/31 10:49:43 by tmorris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_start;
	t_list	*new_lst;

	if (!lst || !f)
		return (NULL);
	new_start = ft_lstnew(f(lst->content));
	if (!new_start)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_lst = ft_lstnew(f(lst->content));
		if (!new_lst)
		{
			ft_lstclear(&new_start, del);
			free(new_start);
			return (NULL);
		}
		ft_lstadd_back(&new_start, new_lst);
		lst = lst->next;
	}
	return (new_start);
}
