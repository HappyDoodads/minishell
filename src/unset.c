/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:58:15 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/31 16:48:41 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_command *cmd, t_misc *misc)
{
	(void)misc;
	ft_dprintf(2, "%s builtin not implemented\n", cmd->argv[0]);
	return (1);
}