#include "minishell.h"

static int	heredoc_loop(char *eof, char **storage)
{
	char	*input;
	int		fd;
	int		eof_len;

	signal(SIGINT, SIG_DFL);
	eof_len = ft_strlen(eof);
	fd = open(*storage, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (print_err(*storage, NULL, NULL));
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
	return (EXIT_SUCCESS);
}

static int	fork_handler(char *eof, char **storage, t_misc *misc)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_err("fork", NULL, NULL));
	if (pid == 0)
	{
		status = heredoc_loop(eof, storage);
		free(eof);
		cleanup(misc);
		exit(status);
	}
	free(eof);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (ft_putchar_fd('\n', 1), EXIT_FAILURE);
	status = WEXITSTATUS(status);
	if (status == EXIT_FAILURE)
		misc->tmpfile_count--;
	return (status);
}

int	ft_heredoc(char *eof, t_misc *misc, char **storage)
{
	char	buf[21];

	if (eof == NULL)
		return (free(eof), print_err("heredoc", NULL, "syntax error"));
	ft_strlcpy(buf, "/.tmpfile", 21);
	ft_itoab(misc->tmpfile_count, &buf[9], 12);
	*storage = ft_strjoin(misc->tmpfile_dir, buf);
	if (*storage == NULL)
		return (free(eof), print_err("malloc", NULL, NULL), ENOMEM);
	misc->tmpfile_count += 1;
	return (fork_handler(eof, storage, misc));
}
