#include "minishell.h"

int	ft_exit(t_command *cmd, t_misc *misc)
{
	int	status = 0;
	(void)(cmd);

	ft_dprintf(2, "%sexit minishell\n%s", RED, RST);
	// if (cmd->argv[1])
	// 	status = ft_atoi(cmd->argv[1]);
	// else
	//	status = misc->prev_status;
	ft_lstclear(&misc->cmd_list, free_command);
	ft_free_split(misc->envp);
	close_all(misc->fd_arr, -1, -1);
	clear_history();
	close(STDIN_DUP);
	close(STDOUT_DUP);
	exit(status);
	return (errno);
}
