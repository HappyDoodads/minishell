#include "minishell.h"

int	ft_cd(t_command *cmd)
{
	if (cmd->argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	if (chdir(cmd->argv[1]))
		return (EXIT_SUCCESS);
	// print_error_msg("cd", cmd->argv[1], NULL);
	return (EXIT_FAILURE);
}
