#include "minishell.h"

static void	heredoc_loop(int fd, char *eof, char *input)
{
	while ((1))
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
		{
			close(fd);
			free(input);
			break ;
		}
		ft_dprintf(fd, "%s\n", input);
		free(input);
	}
}

int	ft_heredoc(char *eof, t_misc *misc, char **storage)
{
	int		fd;
	char	*input;
	char	*tmp;

	tmp = NULL;
	input = NULL;
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
	heredoc_loop(fd, eof, input);
	free(eof);
	return (EXIT_SUCCESS);
}
