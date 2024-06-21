#include "minishell.h"

int	ft_unset(t_command *cmd, t_misc *misc)
{
	(void)misc;
	ft_dprintf(2, "%s builtin not implemented\n", cmd->argv[0]);
	return (1);
}