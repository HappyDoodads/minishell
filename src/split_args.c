#include "libft.h"

static unsigned int	ft_arglen(const char *str)
{
	unsigned int	len;
	int				i;
	char			quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i] && (str[i] != ' ' || quote != 0))
	{
		if (quote == 0 && (str[i] == 34 || str[i] == 39))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
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
			while (*str && (*str != ' ' || quote != 0))
			{
				if (quote == 0 && (*str == 34 || *str == 39))
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

	split = malloc(ft_arglen(*str) + 1);
	if (!split)
		return (NULL);
	i = 0;
	quote = 0;
	while (**str && (**str != ' ' || quote != 0))
	{
		if (quote == 0 && (**str == 34 || **str == 39))
			quote = **str;
		else if (quote == **str)
			quote = 0;
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
	if (i == 0)
		return (NULL);
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