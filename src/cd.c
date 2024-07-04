#include "minishell.h"

static void	update_pwd(char *new_path, t_misc *misc)
{
	char	*v_name;
	char	*tmp;

	v_name = ft_strdup("PWD");
	tmp = ft_strdup(new_path);
	new_path = ft_strjoin("=", tmp);
	free(tmp);
	ft_loopenv(misc, v_name, new_path);
}

static void	update_old_pwd(char *old_path, t_misc *misc)
{
	char	*v_name;
	char	*tmp;

	v_name = ft_strdup("OLD_PWD");
	tmp = ft_strdup(old_path);
	old_path = ft_strjoin("=", tmp);
	free(tmp);
	ft_loopenv(misc, v_name, old_path);
}

int	ft_cd(t_command *cmd, t_misc *misc)
{
	char	new_path[PATH_MAX];
	char	old_path[PATH_MAX];

	if (cmd->argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	getcwd(old_path, PATH_MAX);
	if (chdir(cmd->argv[1]) == 0)
	{
		getcwd(new_path, PATH_MAX);
		update_pwd(new_path, misc);
		update_old_pwd(old_path, misc);
		return (EXIT_SUCCESS);
	}
	return (print_err("cd", cmd->argv[1], NULL));
}
