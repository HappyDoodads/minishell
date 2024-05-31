/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:59:02 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/31 16:47:36 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_command *cmd, t_misc *misc)
{
	(void)misc;
	ft_dprintf(2, "%s builtin not implemented\n", cmd->argv[0]);
	return (1);
}