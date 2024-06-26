#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	unsigned int	i;
	char			end;

	i = 1;
	end = '\n';
	if (cmd->argv[i] != NULL && ft_strncmp(cmd->argv[i], "-n", 3) == 0)
	{
		end = 0;
		i++;
	}
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i++], cmd->wr_fd);
		if (cmd->argv[i] != NULL)
			ft_putchar_fd(' ', cmd->wr_fd);
	}
	if (end)
		ft_putchar_fd(end, cmd->wr_fd);
	return (0);
}