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

void	free_envp(t_envp *envp)
{
	int	i;

	i = -1;
	while (envp[++i].name)
	{
		free(envp[i].name);
		free(envp[i].val);
	}
	ft_bzero(envp, i * sizeof(t_envp));
	free(envp);
}

void	cleanup(t_misc *misc)
{
	ft_lstclear(&misc->cmd_list, free_command);
	free_envp(misc->envp);
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
	char	file[PATH_MAX];
	char	*num;
	size_t	buf_left;

	ft_strlcpy(file, misc->tmpfile_dir, PATH_MAX);
	ft_strlcat(file, "/.tmpfile", PATH_MAX);
	buf_left = ft_strlen(file);
	num = file + buf_left;
	buf_left = PATH_MAX - buf_left;
	while (misc->tmpfile_count > 0)
	{
		ft_itoab(--misc->tmpfile_count, num, buf_left);
		if (unlink(file) == -1)
			print_err(file, NULL, NULL);
	}
}
