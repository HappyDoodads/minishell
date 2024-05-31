/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:58:45 by jcoquet           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/31 17:00:04 by jcoquet          ###   ########.fr       */
=======
/*   Updated: 2024/05/31 16:46:26 by jdemers          ###   ########.fr       */
>>>>>>> faafb70c3f2f729ad1304930ba299bdbf2026d13
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_command *cmd, t_misc *misc)
{
<<<<<<< HEAD
	int	i;
	
	i = 0;
	while(misc->envp[i])
		ft_dprintf(cmd->wr_fd, "%s\n", misc->envp[i++]);
=======
	(void)misc;
	ft_dprintf(2, "%s builtin not implemented\n", cmd->argv[0]);
>>>>>>> faafb70c3f2f729ad1304930ba299bdbf2026d13
	return (1);
}