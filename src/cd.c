#include "minishell.h"

//	Doit modifier $OLDPWD et $PWD avec ft_export
int	ft_cd(t_command *cmd, t_misc *misc)
{
	(void)misc;
	ft_dprintf(2, "%s builtin not implemented\n", cmd->argv[0]);
	return (1);
}