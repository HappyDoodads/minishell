#include "minishell.h"

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

static	void	get_v_val(t_command *cmd, int i, char **v_name, char **v_val)
{
	char	*equal_sign;
	int		size_name;

	equal_sign = ft_strchr(cmd->argv[i], '=');
	size_name = 0;
	if (equal_sign != NULL)
	{
		*v_val = equal_sign;
		size_name = ft_strlen(cmd->argv[i]) - ft_strlen(*v_val);
		*v_name = ft_substr(cmd->argv[i], 0, size_name);
	}
	else if (equal_sign == NULL)
	{
		*v_name = ft_strdup(cmd->argv[i]);
		*v_val = "";
	}
}

static int	equal_sign_handler(t_command *cmd, t_misc *misc, int i)
{
	char	*v_name;
	char	*v_val;

	v_name = NULL;
	v_val = NULL;
	get_v_val(cmd, i, &v_name, &v_val);
	if (ft_isvalid_envname(v_name) == 0)
		ft_loopenv(misc, v_name, v_val);
	free(v_name);
	return (0);
}

int	ft_export(t_command *cmd, t_misc *misc)
{
	int		i;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (ft_ascii_sort(cmd, misc), EXIT_SUCCESS);
	while (cmd->argv[++i])
		equal_sign_handler(cmd, misc, i);
	return (EXIT_SUCCESS);
}
