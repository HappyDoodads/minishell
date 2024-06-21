#include "minishell.h"

int	ft_env(t_command *cmd, t_misc *misc)
{
	int	i;
	
	i = 0;
	if (!misc->envp[i])
		return (0);
	while (misc->envp[i])
		ft_dprintf(cmd->wr_fd, "%s\n", misc->envp[i++]);
	return (1);
}