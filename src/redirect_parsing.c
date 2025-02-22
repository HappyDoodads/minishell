/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:21 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/22 15:12:53 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sort_redirect(char *arg, int type, t_command *cmd, t_misc *misc)
{
	char	**storage;

	if (type >= OUTPUT)
		storage = &(cmd->outfile);
	else
		storage = &(cmd->infile);
	free(*storage);
	if (type == HEREDOC)
	{
		*storage = ft_heredoc(arg, misc);
		if (*storage == NULL)
			return (set_stat(ENOMEM), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (type == OUTPUT)
		cmd->append_out = false;
	else if (type == APPEND)
		cmd->append_out = true;
	*storage = substitute(arg, misc, FILENAME);
	if (!*storage)
		return (set_stat(ENOMEM), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*arg_parsing(char *cmd_str, int *i)
{
	int		j;
	char	*arg;

	while (ft_isspace(cmd_str[*i]))
		(*i)++;
	j = *i;
	if (!cmd_str[j])
		return (set_stat(2), print_err(0, 0, "syntax error"), NULL);
	while (cmd_str[j] && !ft_isspace(cmd_str[j]))
	{
		if (cmd_str[j] == '<' || cmd_str[j] == '>')
			return (set_stat(2), print_err(0, 0, "syntax error"), NULL);
		j = quote_skip(cmd_str, j) + 1;
	}
	arg = ft_substr(cmd_str, *i, j - *i);
	if (!arg)
		return (set_stat(ENOMEM), NULL);
	while (*i < j)
		cmd_str[(*i)++] = ' ';
	*i -= 1;
	return (arg);
}

int	redirect_parsing(char *cmd_str, t_command *cmd, t_misc *misc)
{
	int		i;
	char	type;
	char	*arg;

	i = -1;
	while (cmd_str[++i])
	{
		i = quote_skip(cmd_str, i);
		if (cmd_str[i] != '>' && cmd_str[i] != '<')
			continue ;
		type = cmd_str[i] + (cmd_str[i] == cmd_str[i + 1]);
		cmd_str[i] = ' ';
		if (type == 61 || type == 63)
			cmd_str[i + 1] = ' ';
		arg = arg_parsing(cmd_str, &i);
		if (!arg)
			return (EXIT_FAILURE);
		if (sort_redirect(arg, type, cmd, misc) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
