/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loopadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:38 by jdemers           #+#    #+#             */
/*   Updated: 2024/03/11 17:20:11 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_loopadd_back(t_list **loop, t_list *new)
{
	if (*loop == NULL)
		return (ft_loopadd_front(loop, new));
	new->next = *loop;
	new->prev = (*loop)->prev;
	(*loop)->prev->next = new;
	(*loop)->prev = new;
}

void	ft_loopadd_front(t_list **loop, t_list *new)
{
	if (*loop != NULL)
		ft_loopadd_back(loop, new);
	*loop = new;
}
