/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:48:33 by jdemers           #+#    #+#             */
/*   Updated: 2024/06/28 12:20:57 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->data);
	free(lst);
}

void	ft_lstpop(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if ((*lst)->next)
	{
		tmp = (*lst)->next;
		tmp->prev = (*lst)->prev;
	}
	else if ((*lst)->prev)
	{
		tmp = (*lst)->prev;
		tmp->next = NULL;
	}
	else
		return (ft_lstclear(lst, del));
	ft_lstdelone(*lst, del);
	*lst = tmp;
}

void	ft_void(void *data)
{
	(void)data;
}
