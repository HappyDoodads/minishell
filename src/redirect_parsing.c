/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:21 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/17 16:44:50 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sort_redirect(char *arg, int type, t_command *cmd, t_misc *misc)
{
	char	**storage;
	int		stat;

	if (type == '>' || type == '>' + 1)
		storage = &(cmd->outfile);
	else
		storage = &(cmd->infile);
	if (type == '>')
		cmd->append_out = false;
	else if (type == '>' + 1)
		cmd->append_out = true;
	free(*storage);
	*storage = NULL;
	if (type == '<' + 1)
	{
		stat = ft_heredoc(arg, misc, storage);
		if (stat != EXIT_SUCCESS)
			set_stat(stat, misc);
		return (stat);
	}
	else
		*storage = arg;
	return (EXIT_SUCCESS);
}

static char	*arg_parsing(char *cmd_str, int *i, char type, t_misc *misc)
{
	int		j;
	char	*arg;

	while (ft_isspace(cmd_str[*i]))
		(*i)++;
	j = *i;
	if (!cmd_str[j])
		return (set_stat(2, misc), print_err(0, 0, "syntax error"), NULL);
	while (cmd_str[j] && !ft_isspace(cmd_str[j]))
	{
		if (cmd_str[j] == '<' || cmd_str[j] == '>')
			return (set_stat(2, misc), print_err(0, 0, "syntax error"), NULL);
		j = quote_skip(cmd_str, j, misc) + 1;
	}
	arg = ft_substr(cmd_str, *i, j - *i);
	arg = substitute(arg, misc, false, type == 61);
	if (!arg)
		return (set_stat(ENOMEM, misc), NULL);
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
		i = quote_skip(cmd_str, i, misc);
		if (cmd_str[i] != '>' && cmd_str[i] != '<')
			continue ;
		type = cmd_str[i] + (cmd_str[i] == cmd_str[i + 1]);
		cmd_str[i] = ' ';
		if (type == 61 || type == 63)
			cmd_str[i + 1] = ' ';
		arg = arg_parsing(cmd_str, &i, type, misc);
		if (!arg)
			return (EXIT_FAILURE);
		if (sort_redirect(arg, type, cmd, misc) != EXIT_SUCCESS)
			return (free(arg), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
