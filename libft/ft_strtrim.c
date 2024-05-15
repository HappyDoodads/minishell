/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:37:34 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/20 07:33:52 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_scan(char *set, char c)
{
	size_t	i;

	set = (char *)set;
	i = 0;
	while (set[i])
	{
		if (set[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_search_start(char *s1, char *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (ft_scan(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_search_end(char *s1, char *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (s1[i] > 0)
	{
		if (ft_scan(set, s1[i]) == 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			start;
	size_t			end;
	size_t			len;
	char			*trim;

	if (!s1)
		return (NULL);
	start = ft_search_start((char *)s1, (char *)set);
	end = (ft_search_end((char *)s1, (char *)set) + 1);
	len = end - start;
	if (start > end)
		return (ft_strdup(""));
	trim = (char *)malloc(sizeof(char) * (len + 1));
	if (!trim)
		return (NULL);
	else if (trim == 0)
		return (NULL);
	ft_memmove(trim, s1 + start, len);
	trim[len] = '\0';
	return (trim);
}

// int	main(void)
// {
// 	char	*trimmed;

// 	trimmed = ft_strtrim("ababbabababababbbaaaSALUTbabababababababab", "ab");
// 	if (trimmed)
// 	{
// 		printf("%s", trimmed);
// 		free(trimmed);
// 	}
// 	return (0);
// }
