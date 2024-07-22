/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:14 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/22 15:02:43 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	quote_check(char c, char *quote, int flag)
{
	if (flag == IN_HEREDOC)
		return (false);
	if (*quote == NO_QUOTE && (c == SQUOTE || c == DQUOTE))
		*quote = c;
	else if (*quote == c)
		*quote = NO_QUOTE;
	else
		return (false);
	return (flag != CMD_STR);
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
	return (joined);
}

static char	*append_to_buf(char c, char buf[42], char *res)
{
	int	i;

	if (!res)
	{
		print_err("malloc", NULL, NULL);
		set_stat(ENOMEM);
		return (NULL);
	}
	i = 0;
	while (buf[i] != '\0')
		i++;
	buf[i] = c;
	if (i == 40 || (c == '\0' && i > 0))
		res = reset_buffer(buf, res);
	return (res);
}

static char	*insert_envar(char *v_name, int *arg_i, char *res, t_misc *misc)
{
	char	*tmp;
	char	*v_val;
	size_t	len;

	if (!res)
		return (NULL);
	len = 1;
	if (v_name[0] == '?')
		v_val = ft_itoa(g_status);
	else
	{
		while (ft_isalnum(v_name[len]) || v_name[len] == '_')
			len++;
		v_name = ft_substr(v_name, 0, len);
		if (!v_name)
			return (free(res), NULL);
		v_val = ft_strdup(envp_getval(misc->envp, v_name));
		free(v_name);
	}
	if (!v_val)
		return (free(res), NULL);
	tmp = ft_strjoin(res, v_val);
	*arg_i += len - 1;
	return (free(res), free(v_val), tmp);
}

//	if quote_ign == true, quotation symbols are not removed from string
//	if var_ign == true, env. variable symbol ($) is read as simple text
char	*substitute(char *arg, t_misc *misc, int flag)
{
	char	buf[42];
	char	*res;
	char	quote;
	int		i;

	if (!arg)
		return (set_stat(ENOMEM), print_err("malloc", 0, 0), NULL);
	res = reset_buffer(buf, NULL);
	quote = NO_QUOTE;
	i = -1;
	while (arg[++i] && res != NULL)
	{
		if (quote_check(arg[i], &quote, flag))
			continue ;
		else if (flag != NO_SUBST && arg[i] == '$' && quote != SQUOTE
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
