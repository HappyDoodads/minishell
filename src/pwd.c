/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:23 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/19 15:28:45 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_command *cmd, t_misc *misc)
{
	char	cwd[PATH_MAX];

	(void)misc;
	if (cmd->argv[1] != NULL)
	{
		if (cmd->argv[1][0] == '-')
			return(ft_dprintf(2, "pwd: invalid option: %s\n", cmd->argv[1]), 1);
	}
	getcwd(cwd, PATH_MAX);
	ft_dprintf(cmd->pipe_r[1], "%s\n", cwd);
	return (0);
}
