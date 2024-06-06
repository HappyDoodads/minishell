/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:59:02 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/06 11:44:27 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// trie les env par ascii dans le cas d'un export
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

//replace the value of an existing env var
void	replace_env_var(char **envar_addr, char *var_name, const char *var_value)
{
	if (var_name == NULL)
		exit(EXIT_FAILURE);
	free(*envar_addr);
	*envar_addr = ft_strjoin(var_name, var_value);
}

//export var_name=var_value
static void ft_new_export(t_misc *misc, char *var_name, char *var_value)
{
	int 	i;
	char	**cpy_envp;
	char	*new_var;
	
	i = 0;
	//TODO a check si value est null de creer quand meme l'export
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
	free(misc->envp);
	misc->envp = cpy_envp;
}

//init var_name and var_value
static	void	ft_init_varenv(char *var_name, char *var_value, t_command *cmd, int i)
{
	var_value = ft_strchr(cmd->argv[i], '=');
	if (var_value[0] == '=' && var_value[1] == '\0') // si '=' et rien apres
		return(ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", cmd->argv[i]), EXIT_FAILURE);
	var_name = ft_substr(cmd->argv[i], 0, (ft_strlen(cmd->argv[i]) - ft_strlen(var_value)));
}

//check dans les envp si la variable existe
static	void	ft_loopenv(t_command *cmd, t_misc *misc, char *var_name, char *var_value)
{
	int		j;
	int		flag;

	flag = 0;
	j = 0;
	while (misc->envp[j])// boucle sur les envp
			{
				if(strncmp(misc->envp[j], var_name, ft_strlen(var_name)) == 0 && ft_isvalid_envname(var_name))// si le nom de la variable existe
				{
					replace_env_var(&misc->envp[j], var_name, var_value);
					flag = 1;
				}
				else if (ft_isvalid_envname(var_name))
					ft_dprintf(cmd->wr_fd, "minishell: export: %s: not a valid identifier", var_name);
				j++;
			}
			if (!flag)
			{
				ft_new_export(misc, var_name, var_value);
				flag = 0;
			}
}

int	ft_export(t_command *cmd, t_misc *misc)
{
	int		i;
	int		j;
	int		flag;
	char	*var_name;
	char	*var_value;

	i = 1;
	j = 0;
	flag = 0;

	if (cmd->argv[1] == NULL)
		return (ft_ascii_sort(cmd, misc), EXIT_SUCCESS);
	while (cmd->argv[i]) // boucle sur les arguments
	{
		ft_init_varenv(var_name, var_value, cmd, i);
		while (!ft_strchr(cmd->argv[i], '=') && cmd->argv[i])// si pas de '=' ET non NULL;
		{
			ft_new_export(misc, cmd->argv[i], "");
			i++;
			continue ;
		}
		if (ft_isvalid_envname(var_name) == 1)
		{
			i++;
			continue ;
		}
		if (ft_strchr(cmd->argv[i], '=' && var_name != NULL)) // si '=' et non valide
		{
			ft_loopenv(cmd, misc, var_name, var_value);
			if (!flag)
			{
				ft_new_export(misc, var_name, var_value);
				flag = 0;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
