/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:56:53 by jdemers           #+#    #+#             */
/*   Updated: 2024/03/21 18:14:05 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, void (*del)(void *))
{
	t_list	*target;

	target = *lst;
	target->prev->next = target->next;
	target->next->prev = target->prev;
	if (target->next == NULL)
		*lst = target->prev;
	else
		*lst = target->next;
	ft_lstdelone(target, del);
}
