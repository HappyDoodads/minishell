#include "minishell.h"

static unsigned int	ft_arglen(const char *str)
{
	unsigned int	len;
	int				i;
	char			quote;

	i = 0;
	len = 0;
	quote = NO_QUOTE;
	while (str[i] && (str[i] != ' ' || quote))
	{
		if (quote == NO_QUOTE && (str[i] == DQUOTE || str[i] == QUOTE))
			quote = str[i];
		else if (quote == str[i])
			quote = NO_QUOTE;
		else
			len++;
		i++;
	}
	return (len);
}

static unsigned int	count_args(const char *str)
{
	unsigned int	i;
	char			quote;

	i = 0;
	quote = 0;
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
					quote = 0;
				str++;
			}
		}
	}
	return (i);
}

static char	*sub_split(char const **str)
{
	unsigned int	i;
	char			*split;
	char			quote;

	split = ft_calloc(ft_arglen(*str) + 1, sizeof(char));
	if (!split)
		return (NULL);
	i = 0;
	quote = NO_QUOTE;
	while (**str && (**str != ' ' || quote))
	{
		if (quote == NO_QUOTE && (**str == DQUOTE || **str == QUOTE))
			quote = **str;
		else if (quote == **str)
			quote = NO_QUOTE;
		else
			split[i++] = **str;
		(*str)++;
	}
	split[i] = '\0';
	return (split);
}

char	**split_args(const char *s)
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
			if (!argv[i++])
				return (ft_free_split(argv), NULL);
		}
	}
	return (argv);
}
