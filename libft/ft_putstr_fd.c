/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:27:14 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/13 16:48:44 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*ptr_s;

	ptr_s = s;
	while (*ptr_s)
	{
		write(fd, ptr_s, 1);
		ptr_s++;
	}
}

// int	main(void)
// {	
// 	ft_putstr_fd("\nft_pustr_fd ecrit une chaine de caractere\n\n", 1);
// 	return (0);
// }