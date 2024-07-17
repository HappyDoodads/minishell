/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:25 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/17 15:38:22 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_skip(char *line, int i, t_misc *misc)
{
	char	quote;

	if (line[i] != SQUOTE && line[i] != DQUOTE)
		return (i);
	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		return (i);
	print_err(NULL, NULL, "syntax error");
	set_stat(2, misc);
	return (-1);
}

static t_command	*malloc_cmd(char *cmd_str, t_list **cmd_list, t_misc *misc)
{
	t_command	*command;
	t_list		*new;

	if (!cmd_str)
		return (set_stat(ENOMEM, misc), print_err("malloc", 0, 0), NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
	{
		free(cmd_str);
		return (set_stat(ENOMEM, misc), print_err("malloc", 0, 0), NULL);
	}
	new = ft_lstnew(command);
	if (!new)
	{
		free(cmd_str);
		free(command);
		return (set_stat(ENOMEM, misc), print_err("malloc", 0, 0), NULL);
	}
	ft_lstadd_back(cmd_list, new);
	return (command);
}

static int	parse_cmd(char *cmd_str, t_list **cmd_list, t_misc *misc)
{
	t_command	*command;

	command = malloc_cmd(cmd_str, cmd_list, misc);
	if (!command)
		return (EXIT_FAILURE);
	command->pipe_r[1] = 1;
	if (redirect_parsing(cmd_str, command, misc) != EXIT_SUCCESS)
		return (free(cmd_str), EXIT_FAILURE);
	cmd_str = substitute(cmd_str, misc, true, false);
	if (!cmd_str)
		return (set_stat(ENOMEM, misc), print_err("malloc", NULL, NULL));
	command->argv = split_args(cmd_str, misc);
	free(cmd_str);
	if (command->argv == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_list	*parse_input(char *input, t_misc *misc)
{
	t_list			*cmd_list;
	unsigned int	i_0;
	int				i;
	int				stat;

	i = -1;
	i_0 = 0;
	cmd_list = NULL;
	while (input[++i])
	{
		i = quote_skip(input, i, misc);
		if (i == -1)
			return (ft_lstclear(&cmd_list, free_command), NULL);
		if (input[i] == '|')
		{
			stat = parse_cmd(ft_substr(input, i_0, i - i_0), &cmd_list, misc);
			if (stat != EXIT_SUCCESS)
				return (ft_lstclear(&cmd_list, free_command), NULL);
			i_0 = i + 1;
		}
	}
	stat = parse_cmd(ft_substr(input, i_0, i - i_0), &cmd_list, misc);
	if (stat != EXIT_SUCCESS)
		ft_lstclear(&cmd_list, free_command);
	return (cmd_list);
}
