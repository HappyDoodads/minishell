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
