/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:58:45 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/20 08:28:33 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_command *cmd, t_misc *misc)
{
	int	i;

	i = 0;
	if (!misc->envp[i])
		return (0);
	while (misc->envp[i])
	{
		if (ft_strchr(misc->envp[i], '='))
			ft_dprintf(cmd->wr_fd, "%s\n", misc->envp[i]);
		i++;
	}
	return (1);
}
