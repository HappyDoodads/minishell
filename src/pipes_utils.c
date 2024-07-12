#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_pipe(int pipefd[2])
{
	ft_close(pipefd[0]);
	ft_close(pipefd[1]);
}

void close_cmd_pipes(t_command *cmd)
{
	close_pipe(cmd->pipe_L);
	close_pipe(cmd->pipe_R);
}
