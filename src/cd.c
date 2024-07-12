#include "minishell.h"

int	ft_cd(t_command *cmd, t_misc *misc)
{
	char	new_path[PATH_MAX + 1];
	char	old_path[PATH_MAX + 1];

	if (cmd->argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	old_path[0] = '=';
	new_path[0] = '=';
	getcwd(old_path + 1, PATH_MAX);
	if (chdir(cmd->argv[1]) != 0)
		return (print_err("cd", cmd->argv[1], NULL));
	getcwd(new_path + 1, PATH_MAX);
	export_loopenv(misc, "PWD", new_path);
	export_loopenv(misc, "OLDPWD", old_path);
	return (EXIT_SUCCESS);
}
