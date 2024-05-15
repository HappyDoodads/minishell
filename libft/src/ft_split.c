/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:22:43 by jdemers           #+#    #+#             */
/*   Updated: 2023/12/18 15:01:24 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	ft_wordlen(const char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static unsigned int	count_words(const char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	return (i);
}

static char	*sub_split(char const **str_ptr, char c)
{
	char			*str;
	unsigned int	word_len;

	word_len = ft_wordlen(*str_ptr, c);
	str = ft_substr(*str_ptr, 0, word_len);
	if (!str)
		return (NULL);
	*str_ptr += word_len;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned int	i;

	split = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			split[i] = sub_split(&s, c);
			if (!split[i++])
			{
				split = ft_free_split(split);
				return (NULL);
			}
		}
	}
	split[i] = NULL;
	return (split);
}
