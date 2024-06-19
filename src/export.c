/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:59:02 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/19 15:22:10 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_ascii_sort(t_command *cmd, t_misc *misc)
{
	int		i;
	char	*tmp;
	char	**cpy_envp;
	
	cpy_envp = dup_envp(misc->envp);
	i = 0;
	while (cpy_envp[i] && cpy_envp[i + 1])
	{
		if (ft_strncmp(cpy_envp[i], cpy_envp[i + 1], 1) > 0)
		{
			tmp = cpy_envp[i];
			cpy_envp[i] = cpy_envp[i + 1];
			cpy_envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while(cpy_envp[i])
		ft_dprintf(cmd->wr_fd, "%s\n", cpy_envp[i++]);
	ft_free_split(cpy_envp);
}


void	replace_env_var(char **envar_addr, char *var_name, const char *var_value)
{
	*envar_addr = ft_strjoin(var_name, var_value);
}

static void ft_new_export(t_misc *misc, char *var_name, char *var_value)
{
	int 	i;
	char	**cpy_envp;
	char	*new_var;
	
	i = 0;
	while (misc->envp[i])
		i++;
	cpy_envp = ft_calloc((i + 2), sizeof(char *));
	if(!cpy_envp)
		return ;
	i = 0;
	while (misc->envp[i])
	{
		cpy_envp[i] = misc->envp[i];
		i++;
	}
		
	new_var = ft_strjoin(var_name, var_value);
	cpy_envp[i] = new_var;
	cpy_envp[i + 1] = NULL;
	ft_free_split(misc->envp);
	misc->envp = cpy_envp;
}

int	ft_export(t_command *cmd, t_misc *misc)
{
	int		i;
	int		flag;
	char	*var_name;
	char	*var_value;

	i = 0;
	flag = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_ascii_sort(cmd, misc);
		return (EXIT_SUCCESS);
	}
	var_value = ft_strchr(cmd->argv[1], '=');
	var_name = ft_substr(cmd->argv[1], 0, (ft_strlen(cmd->argv[1]) - ft_strlen(var_value)));
	while (misc->envp[i])
	{
		if (misc->envp[i] && ft_strncmp(misc->envp[i], var_name, ft_strlen(var_name)) == 0)
		{
			replace_env_var(&misc->envp[i], var_name, var_value);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		ft_new_export(misc, var_name, var_value);
	return (0);
}
