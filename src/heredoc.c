
#include "minishell.h"

int	ft_heredoc(char *eof, t_command *cmd, t_misc *misc)
{
	int fd;
	char *input;

	if (eof == NULL)
	{
		ft_dprintf(2, "minishell: syntax error\n");
		return (EXIT_FAILURE);
	}
	cmd->infile = ft_strjoin(".tmpfile", ft_itoa(misc->tmpfile_count++));
	fd = open(cmd->infile, O_CREAT | O_RDWR | O_APPEND, 0644);
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
	free(eof);
	return (0);
}
