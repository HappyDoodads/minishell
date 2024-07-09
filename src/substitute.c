#include "minishell.h"

static bool	quote_check(char c, char *stat, bool quote_flag)
{
	if (quote_flag)
		return (false);
	if (*stat == NO_QUOTE && (c == QUOTE || c == DQUOTE))
		*stat = c;
	else if (*stat == c)
		*stat = NO_QUOTE;
	else
		return (false);
	return (true);
}

static char	*reset_buffer(char buf[42], char *res)
{
	char	*joined;

	if (!res)
		joined = ft_strdup("");
	else
	{
		joined = ft_strjoin(res, buf);
		free(res);
	}
	ft_bzero(buf, 42);
	if (!joined)
		print_err("malloc", NULL, NULL);
	return (joined);
}

static char	*append_to_buf(char c, char buf[42], char *res)
{
	int	i;

	if (!res)
		return (NULL);
	i = 0;
	while (buf[i] != '\0')
		i++;
	buf[i] = c;
	if (i == 40 || (c == '\0' && i > 0))
		res = reset_buffer(buf, res);
	return (res);
}

static char	*insert_envar(char *var_name, int *arg_i, char *res, t_misc *misc)
{
	char	*tmp;
	char	*var_val;
	int		len;
	char	**envp;

	len = 1;
	if (var_name[0] == '?')
		var_val = ft_itoa(misc->prev_status);
	else
	{
		while (ft_isalnum(var_name[len]) || var_name[len] == '_')
			len++;
		envp = misc->envp;
		while (*envp && ft_strncmp(*envp, var_name, len) != 0)
			envp++;
		if (*envp != NULL)
			var_val = ft_substr(*envp, len + 1, ft_strlen(&(*envp)[len + 1]));
		else
			var_val = ft_strdup("");
	}
	if (!var_val)
		return (free(res), print_err("malloc", NULL, NULL), NULL);
	tmp = ft_strjoin(res, var_val);
	*arg_i += len - 1;
	return (free(res), free(var_val), tmp);
}

//	if quote_flag == true, quotation symbols are read as simple text
char	*substitute(char *arg, t_misc *misc, bool quote_flag)
{
	char	buf[42];
	char	*res;
	char	stat;
	int		i;

	if (!arg)
		return (print_err("malloc", NULL, NULL), NULL);
	res = reset_buffer(buf, NULL);
	stat = NO_QUOTE;
	i = -1;
	while (arg[++i] && res != NULL)
	{
		if (quote_check(arg[i], &stat, quote_flag))
			continue ;
		else if (arg[i] == '$' && stat != QUOTE
			&& (ft_isalpha(arg[i + 1]) || ft_isset(arg[i + 1], "_?")))
		{
			i++;
			res = reset_buffer(buf, res);
			res = insert_envar(&arg[i], &i, res, misc);
		}
		else
			res = append_to_buf(arg[i], buf, res);
	}
	return (free(arg), append_to_buf('\0', buf, res));
}
