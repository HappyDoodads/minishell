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
	char	cwd[PATH_MAX];
	(void)misc;

	if (cmd->argv[1] && cmd->argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	if (!chdir(cmd->argv[1]))
	{
		update_pwd(getcwd(cwd, PATH_MAX), misc);
		return (EXIT_SUCCESS);
	}
	perror("minishell: cd");
	return (EXIT_FAILURE);
}
