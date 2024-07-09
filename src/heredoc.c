#include "minishell.h"

static void	heredoc_loop(char *eof, char **storage)
{
	char	*input;
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open(*storage, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	while (1)
	{
		{
			ft_putstr_fd("> ", 1);
			input = get_next_line(0);
			if (ft_strncmp(input, eof, ft_strlen(eof)) == 0 || !input)
			{
				close(fd);
				free(input);
				break ;
			}
			ft_putendl_fd(input, fd);
			free(input);
		}
	}
}

static int	fork_handler(char *eof, t_misc *misc, char **storage)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), EXIT_FAILURE);
	if (pid == 0)
	{
		heredoc_loop(eof, storage);
		exit (0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sigint_handler);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (ft_putchar_fd('\n', 1), EXIT_FAILURE);
		(void)misc;
	}
	return (0);
}

int	ft_heredoc(char *eof, t_misc *misc, char **storage)
{
	char	*tmp;

	if (eof == NULL)
	{
		ft_dprintf(2, "minishell: syntax error\n");
		return (EXIT_FAILURE);
	}
	tmp = ft_itoa(misc->tmpfile_count);
	*storage = ft_strjoin(".tmpfile", tmp);
	free(tmp);
	if (*storage == NULL)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	misc->tmpfile_count += 1;
	fork_handler(eof, misc, storage);
	free(eof);
	return (EXIT_SUCCESS);
}
