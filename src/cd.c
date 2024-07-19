/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:46:55 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/19 15:47:44 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_command *cmd, t_misc *misc)
{
	char	new_path[PATH_MAX + 1];
	char	old_path[PATH_MAX + 1];

	if (cmd->argv[1] != NULL)
	{
		if (cmd->argv[1][0] == '-')
			return(ft_dprintf(2, "cd: invalid option: %s\n", cmd->argv[1]), 1);
	}
	old_path[0] = '=';
	new_path[0] = '=';
	getcwd(old_path + 1, PATH_MAX);
	if (chdir(cmd->argv[1]) != 0)
		return (print_err("cd", cmd->argv[1], NULL));
	getcwd(new_path + 1, PATH_MAX);
	export_loopenv(misc, "PWD", new_path);
	export_loopenv(misc, "OLDPWD", old_path);
	return (EXIT_SUCCESS);
}
