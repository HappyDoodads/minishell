/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:00:56 by jdemers           #+#    #+#             */
/*   Updated: 2023/10/20 14:00:54 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	while (start + i < s_len && i < len)
		i++;
	ss = ft_calloc(i + 1, sizeof(char));
	if (!ss)
		return (NULL);
	i = 0;
	while (start + i < s_len && i < len)
	{
		ss[i] = s[start + i];
		i++;
	}
	return (ss);
}
