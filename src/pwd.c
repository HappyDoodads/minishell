
#include "minishell.h"

int	ft_pwd(t_command *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->argv[1] != NULL)
	{
		if (cmd->argv[1][0] == '-')
			ft_dprintf(2, "pwd: bad option: %s\n", cmd->argv[1]);
		else
			ft_dprintf(2, "pwd: too many arguments\n");
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		if (cmd->wr_fd == 1)
			ft_dprintf(cmd->wr_fd, "%s%s%s\n", YELLOW, cwd, RST);
		else
			ft_dprintf(cmd->wr_fd, "%s\n", cwd);
		return (0);
	}
	perror("getcwd() error");
	return (errno);
}
