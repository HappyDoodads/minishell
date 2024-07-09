#include "minishell.h"

int	ft_env(t_command *cmd, t_misc *misc)
{
	int	i;

	i = 0;
	if (!misc->envp[i])
		return (0);
	while (misc->envp[i])
	{
		if (ft_strchr(misc->envp[i], '='))
			ft_dprintf(cmd->pipe_R[1], "%s\n", misc->envp[i]);
		i++;
	}
	return (1);
}
