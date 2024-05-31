/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:59:02 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/31 16:56:02 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_var(char **envar_addr, char *var_name, const char *var_value)
{
	
}


int	ft_export(t_command *cmd, t_misc *misc)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (ft_env(cmd, misc)); //TODO: ascii sort
	var_value = ft_strchr(cmd->argv[1], '=');
	var_name = ft_substr(cmd->argv[1], 0, var_value - cmd->argv[1]);
	while (misc->envp[i] && ft_strncmp(misc->envp[i], var_name, ft_strlen(var_name)) != 0)	
		i++;
	replace_env_var(&misc->envp[i], var_name, var_value);
		
	misc->envp[i] = ft_strjoin(var_name, var_value);
	if (misc->envp[i] == NULL)
		return (1);
	return (0);
}
