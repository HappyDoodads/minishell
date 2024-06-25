
#include "minishell.h"

int	ft_heredoc(t_command *cmd)
{
	int fd;
	int i = 1; // Index a passer en pointeur lors du parsing
	char *input;
	char *file = ft_strjoin(".tmpfile", ft_itoa(i)); // creation tmp file pour heredoc
	if (cmd->argv[1] == NULL)
	{
		ft_dprintf(2, "minishell: syntax error\n");
		return (EXIT_FAILURE);
	}
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	while ((1))
	{
		input = readline("> ");
		if (strncmp(input, cmd->argv[1], ft_strlen(cmd->argv[1])) == 0)
		{
			close(fd);
			free(input);
			break ;
		}
		ft_dprintf(fd, "%s\n", input);
			free(input);
	}
	return (0);
}