#include"minishell.h"

int	redirections(t_command *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			ft_dprintf(2, "minishell: %s: %s\n", cmd->infile, strerror(errno));
			return (1);
		}
		dup2(fd, cmd->rd_fd);
	}
	if (cmd->outfile)
	{
		fd = O_TRUNC;
		if (cmd->append_out)
			fd = O_APPEND;
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | fd);
	}
}