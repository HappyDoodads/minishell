/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:11:38 by jdemers           #+#    #+#             */
/*   Updated: 2024/03/11 18:32:30 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_item;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_item = ft_lstnew((*f)(lst->data));
		if (!new_item)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_item);
		lst = lst->next;
	}
	return (new_list);
}

t_list	*ft_loopmap(t_list *loop, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_loop;
	t_list	*new_item;
	t_list	*start;

	if (!loop || !f || !del)
		return (NULL);
	new_loop = ft_loopnew((*f)(loop->data));
	if (!new_loop)
		return (ft_lstdelone(new_loop, del), NULL);
	start = loop;
	loop = loop->next;
	while (loop != start)
	{
		new_item = ft_loopnew((*f)(loop->data));
		if (!new_item)
			return (ft_loopclear(&new_loop, del), NULL);
		ft_loopadd_back(&new_loop, new_item);
		loop = loop->next;
	}
	return (new_loop);
}
