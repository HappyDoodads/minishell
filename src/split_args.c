/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:16 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/18 14:46:01 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_arglen(const char *str)
{
	unsigned int	len;
	char			quote;

	len = 0;
	quote = NO_QUOTE;
	while (str[len] && (str[len] != ' ' || quote != NO_QUOTE))
	{
		if ((str[len] == DQUOTE || str[len] == SQUOTE) && quote == NO_QUOTE)
			quote = str[len];
		else if (quote == str[len])
			quote = NO_QUOTE;
		len++;
	}
	return (len);
}

static unsigned int	count_args(const char *str)
{
	unsigned int	i;
	char			quote;

	i = 0;
	quote = NO_QUOTE;
	while (*str)
	{
		if (*str == ' ')
			str++;
		else
		{
			i++;
			while (*str && (*str != ' ' || quote))
			{
				if (quote == NO_QUOTE && (*str == DQUOTE || *str == SQUOTE))
					quote = *str;
				else if (quote == *str)
					quote = NO_QUOTE;
				str++;
			}
		}
	}
	return (i);
}

static char	*sub_split(char const **str)
{
	unsigned int	len;
	char			*split;

	len = ft_arglen(*str);
	split = ft_substr(*str, 0, len);
	if (!split)
		return (NULL);
	*str += len;
	return (split);
}

char	**split_args(const char *s, t_misc *misc)
{
	char			**argv;
	unsigned int	i;

	i = count_args(s);
	argv = ft_calloc(i + 1, sizeof(char *));
	if (!argv)
		return (set_stat(ENOMEM), print_err("malloc", 0, 0), NULL);
	i = 0;
	while (*s)
	{
		if (ft_isspace(*s))
			s++;
		else
		{
			argv[i] = sub_split(&s);
			argv[i] = substitute(argv[i], misc, false, true);
			if (!argv[i++])
				return (ft_free_split(argv), NULL);
		}
	}
	return (argv);
}
