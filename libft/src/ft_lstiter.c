/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:08:05 by jdemers           #+#    #+#             */
/*   Updated: 2024/03/11 18:40:44 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->data);
		lst = lst->next;
	}
}

void	ft_loopiter(t_list *loop, void (*f)(void *))
{
	t_list	*start;

	start = loop;
	(*f)(loop->data);
	loop = loop->next;
	while (loop != start)
	{
		(*f)(loop->data);
		loop = loop->next;
	}
}
