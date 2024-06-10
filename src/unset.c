/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:58:15 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/10 10:46:17 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalid_envname(char *var_name)
{
	int	i;

	i = 1;
	if (!ft_isalnum(var_name[0]) && var_name[0] != '_')
		return (ft_dprintf(2, "minishell: `%s':\
		not a valid identifier\n", var_name), 1);
	while (var_name[i])
	{
		if (ft_isalpha(var_name[i]) && var_name[i] != '_')
			return (ft_dprintf(2, "minishell: `%s':\
			not a valid identifier\n", var_name), 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_command *cmd, t_misc *misc)
{
	int		i;
	int		j;
	int		k;
	char	**cpy_envp;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (EXIT_SUCCESS);
	while (cmd->argv[++i])
	{
		j = 0;
		k = 0;
		while (misc->envp[j])
			j++;
		cpy_envp = ft_calloc((j), sizeof(char *));
		if (!cpy_envp)
			return (EXIT_FAILURE);
		j = 0;
		while (misc->envp[j])
		{
			if (ft_strncmp(misc->envp[j], cmd->argv[i], \
			ft_strlen(cmd->argv[i])) != 0)
			{
				cpy_envp[k] = misc->envp[j];
				k++;
			}
			else
				free(misc->envp[j]);
			j++;
		}
		cpy_envp[k] = NULL;
		free(misc->envp);
		misc->envp = cpy_envp;
	}
	return (EXIT_SUCCESS);
}
