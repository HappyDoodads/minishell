
#include "minishell.h"

static void	ft_ascii_sort(t_command *cmd, t_misc *misc)
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
	while (cpy_envp[i])
		ft_dprintf(cmd->wr_fd, "%s\n", cpy_envp[i++]);
	ft_free_split(cpy_envp);
}

void	replace_env_var(char **envar_addr, char *var_name, char *var_value)
{
	if (var_name == NULL)
		exit(EXIT_FAILURE);
	free(*envar_addr);
	*envar_addr = ft_strjoin(var_name, var_value);
}

static void	ft_new_export(t_misc *misc, char *var_name, char *var_value)
{
	int		i;
	char	**cpy_envp;
	char	*new_var;

	i = 0;
	while (misc->envp[i])
		i++;
	cpy_envp = ft_calloc((i + 2), sizeof(char *));
	if (!cpy_envp)
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

static	void	ft_loopenv(t_misc *misc, char *var_name, char *var_value)
{
	int		j;
	int		flag;

	flag = 0;
	j = 0;
	while (misc->envp[j])
	{
		if ((ft_strncmp(misc->envp[j], var_name, ft_strlen(var_name)) == 0
				&& !ft_isvalid_envname(var_name)
				&& misc->envp[j][strlen(var_name)] == '=')
			|| misc->envp[j][strlen(var_name)] == '\0')
		{
			replace_env_var(&misc->envp[j], var_name, var_value);
			flag = 1;
		}
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
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (ft_ascii_sort(cmd, misc), EXIT_SUCCESS);
	while (cmd->argv[++i])
	{
		equal_sign = ft_strchr(cmd->argv[i], '=');
		if (equal_sign != NULL)
		{
			if (equal_sign == cmd->argv[i])
				return (ft_dprintf(2, "minishell: export: `%s`: not a valid identifier\n", cmd->argv[i]), EXIT_FAILURE);
			var_value = equal_sign;
			var_name = ft_substr(cmd->argv[i], 0, (ft_strlen(cmd->argv[i]) - ft_strlen(var_value)));
		}
		else
		{
			if (ft_isvalid_envname(cmd->argv[i]) == 0)
			{
				var_name = cmd->argv[i];
				var_value = "";
			}
		}
		if (ft_isvalid_envname(var_name) == 0)
		{
			ft_loopenv(misc, var_name, var_value);
			free(var_name);
		}
		else 
		{
			free(var_name);
			return (ft_dprintf(2, "minishell: export: `%s`: not a valid identifier\n", var_name), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}