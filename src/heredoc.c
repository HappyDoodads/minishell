#include "minishell.h"

static void	heredoc_loop(char *eof, char **storage, t_misc *misc)
{
	char	*input;
	int		fd;
	int		eof_len;

	signal(SIGINT, SIG_DFL);
	eof_len = ft_strlen(eof);
	fd = open(*storage, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		input = get_next_line(0);
		if (!input)
			break ;
		if (ft_strncmp(input, eof, eof_len) == 0 && input[eof_len] == '\n')
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		free(input);
	}
	close(fd);
	cleanup(misc);
	exit(EXIT_SUCCESS);
}

static int	fork_handler(char *eof, char **storage, t_misc *misc)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), EXIT_FAILURE);
	if (pid == 0)
		heredoc_loop(eof, storage, misc);
	free(eof);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (ft_putchar_fd('\n', 1), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	return (fork_handler(eof, storage, misc));
}
