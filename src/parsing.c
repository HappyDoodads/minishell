/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:42 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/20 18:27:53 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

parse_input(char *cmdline)
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
			i = quote_skip(cmdline, i);
		else if (cmdline[i] == '|')
		{
			parse_cmd(ft_substr(cmdline, start, i - start), pipefd, cmd_list);
			start = i + 1;
		}
	}
}

void	parse_cmd(char *cmd_str, int pipefd[2], t_list **cmd_list)
{
	t_command	*command;
	int			i;
	int			argc;

	command = malloc(sizeof(t_command));
	command->fd_in = pipefd[0];
	pipe(pipefd);
	command->fd_out = pipefd[1];
	i = -1;
	argc = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == ' ')
			i++;
		else
		{
			if (cmd_str[i] == '<' || cmd_str[i] == '>')
			{
				i = parse_redirect(command, cmd_str, i);
				continue ;
			}
			argc++;
			while (cmd_str[i] && cmd_str[i] != ' ')
			{
				if (cmd_str[i] == 34 || cmd_str[i] == 39)
					i = quote_skip(cmd_str, i);
				else if (cmd_str[i] == '<' || cmd_str[i] == '>')
				{
					i = parse_redirect(command, cmd_str, i);
					break ;
				}
				i++;
			}
		}
	}
	free(cmd_str);
}

int	parse_redirect(t_command *command, char *cmd_str, int i)
{
	char	*filename;
	char	redirect;
	int		len;
	int		quote_stat;

	redirect = cmd_str[i++];
	while (cmd_str[i] == ' ')
		i++;
	len = 0;
	while (cmd_str[i] && cmd_str[i] != ' ')
	{
		
	}
}

int	quote_skip(char *line, int i)
{
	int	j;

	j = i + 1;
	while (line[j] && line[j] != line[i])
		j++;
	if (line[j])
		return (j);
	return (i);
}