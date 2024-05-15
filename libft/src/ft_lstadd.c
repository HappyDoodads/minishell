/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:15:42 by jdemers           #+#    #+#             */
/*   Updated: 2024/03/11 16:38:24 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	if (*lst != NULL)
		(*lst)->prev = new;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

void	ft_lstadd_after(t_list **lst, t_list *new)
{
	if (!*lst)
		return (ft_lstadd_front(lst, new));
	new->prev = *lst;
	new->next = (*lst)->next;
	new->next->prev = new;
	(*lst)->next = new;
}
