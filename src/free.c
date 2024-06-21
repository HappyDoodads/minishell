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