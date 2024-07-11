/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:26:52 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/11 16:49:32 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s3 = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (*s1)
		s3[i++] = *(s1++);
	while (*s2)
		s3[i++] = *(s2++);
	return (s3);
}

char	*ft_str3join(char const *s1, char const *s2, char const *s3)
{
	char	*s4;
	size_t	i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s4 = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1, 1);
	if (!s4)
		return (NULL);
	i = 0;
	while (*s1)
		s4[i++] = *(s1++);
	while (*s2)
		s4[i++] = *(s2++);
	while (*s3)
		s4[i++] = *(s3++);
	return (s4);
}
//char	*ft_strnjoin(char const **ss)