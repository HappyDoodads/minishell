#include "minishell.h"

int	ft_exit(t_command *cmd, t_misc *misc)
{
	int	stat;
	int	i;

	ft_dprintf(2, "%sexit minishell\n%s", RED, RST);
	stat = misc->prev_status;
	if (cmd->argv[1])
	{
		i = 0;
		if (cmd->argv[1][0] == '-' && ft_isdigit(cmd->argv[1][1]))
			i += 2;
		while (ft_isdigit(cmd->argv[1][i]))
			i++;
		if (cmd->argv[1][i] == '\0')
			stat = ft_atoi(cmd->argv[1]);
		else
			stat = print_err("exit", cmd->argv[1], "numeric argument required");
	}
	cleanup(misc);
	exit(stat);
	return (errno);
}
