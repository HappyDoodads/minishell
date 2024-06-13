/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:50:22 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/13 11:39:43 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_command *cmd)
{
	if (cmd->argv[1] && cmd->argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	chdir(cmd->argv[1]);
	if (!chdir(cmd->argv[1]))
		return (EXIT_SUCCESS);
	perror("minishell: cd");
	return (EXIT_FAILURE);
}