/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:50:22 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/31 14:58:31 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Doit modifier $OLDPWD et $PWD avec ft_export
int	ft_cd(t_command *cmd, t_misc *misc)
{
	(void)misc;
	ft_dprintf(2, "%s builtin not implemented\n", cmd->argv[0]);
	return (1);
}