/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:58:15 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/06 09:58:22 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalid_envname(char *var_name) // check si le nom de la variable est valide
{
	int	i;

	i = 1;
	if (!ft_isalnum(var_name[0]) && var_name[0] != '_') // si le premier char n'est pas une lettre ou un digit ou un _ 
		return (ft_dprintf(2, "minishell: `%s': not a valid identifier\n", var_name), 1);
	while (var_name[i])
	{
		if (!ft_isalpha(var_name[i])) // si le reste n'est pas une lettre
			return (ft_dprintf(2, "minishell: `%s': not a valid identifier\n", var_name), 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_command *cmd, t_misc *misc)
{
	int	i;
	
	i = 1;
	while (misc->envp[i])
	{
		if (ft_strncmp(misc->envp[i], cmd->argv[1], ft_strlen(cmd->argv[1])) == 0
			&& (misc->envp[ft_strlen(cmd->argv[1])]) == (char *)'=')
		{
			free(misc->envp[i]);
			misc->envp[i] = NULL;
			break ;
		}
		i++;
	}
	return (0);
}