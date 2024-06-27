#include "minishell.h"

void	update_pwd(char *new_path, t_misc *misc)
{
	char	*v_name;
	char	*tmp;

	v_name = "PWD";
	tmp = new_path;
	new_path = ft_strjoin("=", tmp);
	free(tmp);
	ft_loopenv(misc, v_name, new_path);
}

int	ft_cd(t_command *cmd, t_misc *misc)
{
	if (cmd->argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	if (chdir(cmd->argv[1]))
		return (EXIT_SUCCESS);
	// print_error_msg("cd", cmd->argv[1], NULL);
	return (EXIT_FAILURE);
}
