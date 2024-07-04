#include "minishell.h"

static void	heredoc_loop(int fd, char *eof, char *input, char **storage)
{
	signal(SIGINT, sig_heredoc_handler);
	while (1)
	{
		fd = open(*storage, O_RDWR | O_APPEND, 0644);
		if (access (*storage, R_OK | W_OK) != 0)
		{
			ft_dprintf(2, "permissions forbidden\n");
			close(fd);
			break ;
		}
		else
		{
			input = readline("> ");
			if (ft_strncmp(input, eof, ft_strlen(eof)) == 0 || !input)
			{
				close(fd);
				free(input);
				break ;
			}
			ft_dprintf(fd, "%s\n", input);
			free(input);
		}
	}
}

static int	fork_handler(char *eof, t_misc *misc, char **storage, pid_t	pid)
{
	int		status;
	int		fd;
	char	*input;

	input = NULL;
	if (*storage == NULL)
		return (EXIT_FAILURE);
	misc->tmpfile_count += 1;
	if (pid < 0)
		return (perror("fork failed"), EXIT_FAILURE);
	if (pid == 0)
	{
		fd = open(*storage, O_CREAT | O_RDWR | O_TRUNC, 0644);
		heredoc_loop(fd, eof, input, storage);
		return (0);
	}
	else
	{
		signal (SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		delete_tmpfiles(misc);
		signal(SIGINT, sigint_handler);
		ft_create_prompt(misc);
	}
	return (0);
}

int	ft_heredoc(char *eof, t_misc *misc, char **storage)
{
	char	*tmp;
	pid_t	pid;

	tmp = NULL;
	pid = fork();
	if (eof == NULL)
	{
		ft_dprintf(2, "minishell: syntax error\n");
		return (EXIT_FAILURE);
	}
	tmp = ft_itoa(misc->tmpfile_count);
	*storage = ft_strjoin(".tmpfile", tmp);
	free(tmp);
	if (*storage == NULL)
		return (EXIT_FAILURE);
	misc->tmpfile_count += 1;
	fork_handler(eof, misc, storage, pid);
	free(eof);
	return (EXIT_SUCCESS);
}
