#include "minishell.h"

static unsigned int	ft_arglen(const char *str)
{
	unsigned int	len;
	char			quote;

	len = 0;
	quote = NO_QUOTE;
	while (str[len] && (str[len] != ' ' || quote != NO_QUOTE))
	{
		if ((str[len] == DQUOTE || str[len] == QUOTE) && quote == NO_QUOTE)
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
				if (quote == NO_QUOTE && (*str == DQUOTE || *str == QUOTE))
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
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == ' ')
			s++;
		else
		{
			argv[i] = sub_split(&s);
			argv[i] = substitute(argv[i], misc, false);
			if (!argv[i++])
				return (ft_free_split(argv), NULL);
		}
	}
	return (argv);
}
