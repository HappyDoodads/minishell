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
		if (ft_isset(cmd->argv[1][0], "-+") && ft_isdigit(cmd->argv[1][1]))
			i += 2;
		while (ft_isdigit(cmd->argv[1][i]))
			i++;
		if (cmd->argv[1][i] == '\0' && !cmd->argv[2])
			stat = ft_atoi(cmd->argv[1]);
		else if (!cmd->argv[2])
		{
			stat = 255;
			print_err("exit", cmd->argv[1], "numeric argument required");
		}
		else
			return (print_err("exit", NULL, "too many arguments"));
	}
	cleanup(misc);
	exit(stat);
}
