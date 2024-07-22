/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:54 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/22 15:58:07 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(t_command *cmd, int i)
{
	int	j;

	j = 0;
	if (cmd->argv[i][j] == '-')
	{
		j++;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] != 'n')
				break ;
			j++;
		}
	}
	return (j);
}

static	void	write_echo(t_command *cmd, int i, char end)
{
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i++], cmd->pipe_r[1]);
		if (cmd->argv[i] != NULL)
			ft_putchar_fd(' ', cmd->pipe_r[1]);
	}
	if (end)
		ft_putchar_fd(end, cmd->pipe_r[1]);
}

int	ft_echo(t_command *cmd, t_misc *misc)
{
	int		i;
	int		j;
	char	end;

	i = 1;
	end = '\n';
	(void)misc;
	while (cmd->argv[i])
	{
		j = check_option(cmd, i);
		if (cmd->argv[i][j] == '\0' && cmd->argv[i][0] != 0)
		{
			i++;
			j = 0;
			end = 0;
		}
		else
			break ;
	}
	write_echo(cmd, i, end);
	return (0);
}
