/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:32:40 by jdemers           #+#    #+#             */
/*   Updated: 2024/03/11 18:06:31 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_loopsize(t_list *loop)
{
	t_list	*start;
	int		i;

	if (loop == NULL)
		return (0);
	start = loop;
	loop = loop->next;
	i = 1;
	while (loop != start)
	{
		i++;
		loop = loop->next;
	}
	return (i);
}
