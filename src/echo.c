/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:54 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/17 17:13:06 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int option_n(t_command *cmd, unsigned int *i, char *end)
{
	unsigned int	j;
	int				flag;

	flag = 2;
	while (cmd->argv[*i] && !ft_strncmp(cmd->argv[*i], "-n", 2))
	{
		j = 2;
		*end = 0;
		while (cmd->argv[*i][j])
		{
			if (cmd->argv[*i][j] != 'n' && cmd->argv[*i][j] != '\0')
			{
				flag = *i;
				break ;
			}
			j++;
		}
		if (flag != 2)
            break ;
		(*i)++;
	}
	return (flag);
}

int	ft_echo(t_command *cmd, t_misc *misc)
{
	unsigned int	i;
	char			end;
	int 			flag;

	(void)misc;
	i = 1;
	end = '\n';
	flag = option_n(cmd, &i, &end);
	if (end == 0)
        i = flag;
	else
		i = 1;
	 while (cmd->argv[i] != NULL)
    {
        ft_putstr_fd(cmd->argv[i++], cmd->pipe_r[1]);
        if (cmd->argv[i] != NULL)
            ft_putchar_fd(' ', cmd->pipe_r[1]);
    }
    if (end)
        ft_putchar_fd(end, cmd->pipe_r[1]);
    return (0);
}
