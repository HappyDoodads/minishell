#include "minishell.h"

int	ft_echo(t_command *cmd, t_misc *misc)
{
	unsigned int	i;
	char			end;

	(void)misc;
	i = 1;
	end = '\n';
	if (cmd->argv[i] != NULL && ft_strncmp(cmd->argv[i], "-n", 3) == 0)
	{
		end = 0;
		i++;
	}
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i++], cmd->pipe_r[1]);
		if (cmd->argv[i] != NULL)
			ft_putchar_fd(' ', cmd->pipe_r[1]);
	}
	if (end)
		ft_putchar_fd(end, cmd->pipe_r[1]);
	return (0);
}
