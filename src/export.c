/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:59:02 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/31 16:50:55 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_ascii_sort(t_command *cmd, t_misc *misc)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (misc->envp[i] && misc->envp[i + 1])
	{
		if (ft_strncmp(misc->envp[i], misc->envp[i + 1], 1) > 0)
		{
			tmp = misc->envp[i],
			misc->envp[i] = misc->envp[i + 1];
			misc->envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while(misc->envp[i])
		ft_dprintf(cmd->wr_fd, "%s\n", misc->envp[i++]);
}

void	replace_env_var(char **envar_addr, char *var_name, const char *var_value)
{
	*envar_addr = ft_strjoin(var_name, var_value);
}


int	ft_export(t_command *cmd, t_misc *misc)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_ascii_sort(cmd, misc);
		return (EXIT_SUCCESS);
	}
	var_value = ft_strchr(cmd->argv[1], '=');
	if (var_value == NULL)
		return (EXIT_FAILURE);
	var_name = ft_substr(cmd->argv[1], 0, var_value - cmd->argv[1]);
	if (var_name == NULL)
		return (EXIT_FAILURE);
	while (misc->envp[i] && ft_strncmp(misc->envp[i], var_name, ft_strlen(var_name)) != 0)	
		i++;
	replace_env_var(&misc->envp[i], var_name, var_value);
	misc->envp[i] = ft_strjoin(var_name, var_value);
	if (misc->envp[i] == NULL)
		return (1);
	return (0);
}
