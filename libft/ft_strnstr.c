/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:31:52 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/21 12:02:10 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	g;

	i = 0;
	g = 0;
	if (! haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		g = 0;
		while (haystack[i] && haystack[i] == needle[g] && (i < len))
		{
			i++;
			g++;
		}
		if (!needle[g])
			return ((char *)&haystack[(i - g)]);
		i = (i - g) + 1;
	}
	return (NULL);
}

// int main()
// {
// 	char *str = "MZIRIBMZIRIBMZE123";
// 	char *to_find = "MZIRIBMZE";
// 	size_t n = sizeof(to_find);
// 	char *result = ft_strnstr(str, to_find, n);
// 	printf("%s", result);
// }
