/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:42 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 17:47:44 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command *cmd, t_misc *misc)
{
	int	stat;
	int	i;

	stat = misc->prev_status;
	if (cmd->argv[1])
	{
		i = 0;
		if (ft_isset(cmd->argv[1][0], "-+") && ft_isdigit(cmd->argv[1][1]))
			i += 2;
		while (ft_isdigit(cmd->argv[1][i]))
			i++;
		if (cmd->argv[1][i] == '\0' && !cmd->argv[2])
			stat = ft_atoi(cmd->argv[1]);
		else if (!cmd->argv[2])
		{
			stat = 255;
			print_err("exit", cmd->argv[1], "numeric argument required");
		}
		else
			return (print_err("exit", NULL, "too many arguments"));
	}
	misc->exit_flag = true;
	return (stat);
}
