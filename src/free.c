#include "minishell.h"

void	free_command(void *data)
{
	t_command	*command;

	command = data;
	ft_free_split(command->argv);
	command->rd_fd = -1;
	command->wr_fd = -1;
	free(data);
}

void	cleanup(t_misc *misc)
{
	ft_lstclear(&misc->cmd_list, free_command);
	ft_free_split(misc->envp);
	clear_history();
	close(STDIN_DUP);
	close(STDOUT_DUP);
}

void	ft_close(int fd)
{
	if (fd > 1)
		close(fd);
}

void	close_pipe(int pipefd[2])
{
	ft_close(pipefd[0]);
	ft_close(pipefd[1]);
}