#include "minishell.h"

static void	heredoc_loop(int fd, char *eof, char *input, char **storage)
{
	signal(SIGINT, sig_heredoc_handler);
	while (1)
	{
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

int	ft_heredoc(char *eof, t_misc *misc, char **storage)
{
	int		fd;
	char	*input;
	char	*tmp;
	pid_t	pid;
	int		status;

	tmp = NULL;
	input = NULL;
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
	fd = open(*storage, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (pid < 0)
	{
		perror("fork failed");
		close(fd);
		// unlink(*storage);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		heredoc_loop(fd, eof, input, storage);
		// unlink(*storage);
		exit (EXIT_SUCCESS);
	}
	else
	{
		signal (SIGINT, SIG_IGN);g
		waitpid(pid, &status, 0);
		signal(SIGINT, sigint_handler);
		// unlink(*storage);
		ft_create_prompt(misc);
		exit(0);
	}
	free(eof);
	return (EXIT_SUCCESS);
}
