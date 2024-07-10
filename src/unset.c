#include "minishell.h"

bool	ft_isvalid_envname(const char *v_name, const char *context)
{
	int	i;

	i = 1;
	if (!ft_isalpha(v_name[0]) && v_name[0] != '_')
		return (print_err(context, v_name, "not a valid identifier"), false);
	while (ft_isalnum(v_name[i]) || v_name[i] == '_')
		i++;
	if (v_name[i] == '\0')
		return (true);
	return (print_err(context, v_name, "not a valid identifier"), false);
}

static void	loopenv(t_command *cmd, t_misc *misc, char **cpy_envp, int i)
{
	int	j;
	int	k;
	int	len_argv;

	j = 0;
	k = 0;
	len_argv = ft_strlen(cmd->argv[i]);
	while (misc->envp[j])
	{
		if ((ft_strncmp(misc->envp[j], cmd->argv[i], len_argv) == 0)
		&& ((misc->envp[j][len_argv] == '=')
		|| (misc->envp[j][len_argv] == '\0')))
			free(misc->envp[j++]);
		else
			cpy_envp[k++] = misc->envp[j++];
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
		if (!ft_isvalid_envname(cmd->argv[i], "unset"))
			return (EXIT_FAILURE);
		j = 0;
		while (misc->envp[j])
			j++;
		cpy_envp = ft_calloc((j), sizeof(char *));
		if (!cpy_envp)
			return (EXIT_FAILURE);
		loopenv(cmd, misc, cpy_envp, i);
	}
	return (EXIT_SUCCESS);
}
