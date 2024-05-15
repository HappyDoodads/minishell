/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:36:27 by jdemers           #+#    #+#             */
/*   Updated: 2023/10/19 14:38:00 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;
	size_t	nbytes;

	nbytes = count * size;
	alloc = malloc(nbytes);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, nbytes);
	return (alloc);
}
