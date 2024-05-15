/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:26:45 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/21 13:16:38 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s[i] && *f)
	{
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}

// static void	print_index_and_char(unsigned int index, char *c)
// {
// 	printf("Index: %u, Caractère: %c\n", index, *c);
// }

// int	main(void)
// {
// 	printf("Chaîne de départ : %s\n", "hello, world");
// 	ft_striteri("hello, world", print_index_and_char);
// 	return (0);
// }
