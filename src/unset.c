#include "minishell.h"

int	ft_isvalid_envname(char *v_name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(v_name[0]) && v_name[0] != '_')
	{
		ft_dprintf(2, "minishell: `%s': not a valid identifier\n", v_name);
		return (1);
	}
	while (v_name[i])
	{
		if (!ft_isalnum(v_name[i]) && v_name[i] != '_')
			return (ft_dprintf(2, "minishell: `%s': not a valid \
			identifier\n", v_name), 1);
		i++;
	}
	return (0);
}

static void	ft_loopenv(t_command *cmd, t_misc *misc, char **cpy_envp, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (misc->envp[j])
	{
		if (ft_strncmp(misc->envp[j], cmd->argv[i], \
			ft_strlen(cmd->argv[i])) == 0
			&& ((misc->envp[j][ft_strlen(cmd->argv[i])] == '=')
			|| (misc->envp[j][ft_strlen(cmd->argv[i])] == '\0')))
		{
			free(misc->envp[j]);
		}
		else
		{
			cpy_envp[k] = misc->envp[j];
			k++;
		}
		j++;
	}
	cpy_envp[k] = NULL;
	free(misc->envp);
	misc->envp = cpy_envp;
}

int	ft_unset(t_command *cmd, t_misc *misc)
{
	int		i;
	int		j;
	char	**cpy_envp;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (EXIT_SUCCESS);
	while (cmd->argv[++i])
	{
		j = 0;
		while (misc->envp[j])
			j++;
		cpy_envp = ft_calloc((j), sizeof(char *));
		if (!cpy_envp)
			return (EXIT_FAILURE);
		ft_loopenv(cmd, misc, cpy_envp, i);
	}
	return (EXIT_SUCCESS);
}
