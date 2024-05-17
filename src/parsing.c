/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:42 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/17 11:48:26 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

parse_cmdline(char *cmdline)
{
	t_list			**cmd_list;
	int				pipefd[3];
	unsigned int	start;
	int				i;

	i = -1;
	pipefd[2] = 0;
	start = 0;
	while (cmdline[++i])
	{
		if (cmdline[i] == 34 || cmdline[i] == 39)
			i = quote_skip(cmdline, i);
		else if (cmdline[i] == '|')
		{
			pipe(pipefd);
			parse_command(cmdline, start, parser - cmdline, cmd_list);
			start
		}
	}
}

void	parse_command(char *cmdline, unsigned int start, int len, t_list cmd_list)
{
	
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
