#include "minishell.h"

static int	update_env_var(t_envp *env_var, const char *v_val)
{
	free(env_var->val);
	if (v_val)
	{
		env_var->val = ft_strdup(v_val);
		if (!env_var->val)
			return (print_err("malloc", NULL, NULL), ENOMEM);
	}
	else
		env_var->val = NULL;
	return (EXIT_SUCCESS);
}

void	ft_new_export(t_misc *misc, char *v_name, char *v_val)
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
	new_var = ft_strjoin(v_name, v_val);
	cpy_envp[i] = new_var;
	cpy_envp[i + 1] = NULL;
	free(misc->envp);
	misc->envp = cpy_envp;
}

int	export_loopenv(t_misc *misc, const char *v_name, const char *v_val)
{
	int		j;
	int		status;
	size_t	vn_len;

	j = -1;
	status = 1;
	vn_len = ft_strlen(v_name);
	while (misc->envp[++j].name)
	{
		if (ft_strncmp(misc->envp[j].name, v_name, vn_len) == 0)
			status = update_env_var(&misc->envp[j], v_val);
	}
	if (!misc->envp[j].name)
		ft_new_export(misc, v_name, v_val);
}

static int	get_export_var(t_misc *misc, const char *export)
{
	char	*v_name;
	u_int	len;
	int		status;

	len = 0;
	while (export[len] && export[len] != '=')
		len++;
	v_name = ft_substr(export, 0, len);
	if (!v_name)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	if (!ft_isvalid_envname(v_name, "export"))
		status = EXIT_FAILURE;
	else if (export[len])
		status = export_loopenv(misc, v_name, export[len + 1]);
	else
		status = export_loopenv(misc, v_name, NULL);
	free(v_name);
	return (status);
}

int	ft_export(t_command *cmd, t_misc *misc)
{
	int	i;
	int	status;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (ft_ascii_sort(cmd, misc), EXIT_SUCCESS);
	status = EXIT_SUCCESS;
	while (cmd->argv[++i] && status != ENOMEM)
		status = get_export_var(misc, cmd->argv[i]) || status;
	return (status);
}
