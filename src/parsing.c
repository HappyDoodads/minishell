/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:42 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/22 16:11:02 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_skip(char *line, int i)
{
	char	quote;

	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		return (i);
	return (-1);
}

static void	parse_cmd(char *cmd_str, int pipefd[2], t_list **cmd_list)
{
	t_command	*command;
	t_list		*new;

	command = malloc(sizeof(t_command));
	command->fd_in = pipefd[0];
	pipe(pipefd);
	command->fd_out = pipefd[1];
	command->argv = split_args(cmd_str);
	new = ft_lstnew(command);
	ft_lstadd_back(cmd_list, new);
	free(cmd_str);
}

t_list	**parse_input(char *cmdline)
{
	t_list			**cmd_list;
	int				pipefd[2];
	unsigned int	start;
	int				i;

	i = -1;
	pipefd[0] = 0;
	start = 0;
	while (cmdline[++i])
	{
		if (cmdline[i] == 34 || cmdline[i] == 39)
		{
			i = quote_skip(cmdline, i);
			if (i == -1)
				continue ;// Raise badInput error
		}
		else if (cmdline[i] == '|')
		{
			parse_cmd(ft_substr(cmdline, start, i - start), pipefd, cmd_list);
			start = i + 1;
		}
	}
	parse_cmd(ft_substr(cmdline, start, i - start), pipefd, cmd_list);
	return (cmd_list);
}

// int	parse_redirect(t_command *command, char *cmd_str, int i)
// {
// 	char	*filename;
// 	char	redirect;
// 	int		len;
// 	int		quote_stat;

// 	redirect = cmd_str[i++];
// 	quote_stat = NO_QUOTE;
// 	while (cmd_str[i] == ' ')
// 		i++;
// 	len = 0;
// 	while (cmd_str[i] && cmd_str[i] != ' ')
// 	{
		
// 	}
// }