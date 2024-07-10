#include "minishell.h"

void	free_command(void *data)
{
	t_command	*command;

	command = data;
	ft_free_split(command->argv);
	free(command->infile);
	free(command->outfile);
	free(data);
}

void	cleanup(t_misc *misc)
{
	ft_lstclear(&misc->cmd_list, free_command);
	ft_free_split(misc->envp);
	clear_history();
}

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

void	delete_tmpfiles(t_misc *misc)
{
	char	file[20];
	char	*num;

	ft_strlcpy(file, ".tmpfile", 20);
	num = file + 8;
	while (misc->tmpfile_count > 0)
	{
		ft_itoab(--misc->tmpfile_count, num);
		unlink(file);
	}
}
