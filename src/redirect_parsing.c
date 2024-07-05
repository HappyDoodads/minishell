#include "minishell.h"

static int	sort_redirect(char *arg, int type, t_command *cmd, t_misc *misc)
{
	char	**storage;
	int		stat;

	if (type == '>' || type == '>' + 1)
		storage = &(cmd->outfile);
	else
		storage = &(cmd->infile);
	if (type == '>')
		cmd->append_out = false;
	else if (type == '>' + 1)
		cmd->append_out = true;
	free(*storage);
	*storage = NULL;
	if (type == '<' + 1)
	{
		stat = ft_heredoc(arg, misc, storage);
		if (stat != EXIT_SUCCESS)
			set_statcode(stat, misc);
		return (stat);
	}
	else
		*storage = arg;
	return (EXIT_SUCCESS);
}

static int	filename_parsing(char *cmd_str, int i, t_command *cmd, t_misc *misc)
{
	int		j;
	char	type;
	bool	mod;
	char	*filename;

	j = i + 1;
	type = cmd_str[i];
	cmd_str[i] = ' ';
	mod = type == cmd_str[j];
	if (mod)
		cmd_str[j++] = ' ';
	while (cmd_str[j] == ' ')
		j++;
	i = j;
	while (cmd_str[j] && cmd_str[j] != ' ')
		j = quote_skip(cmd_str, j) + 1;
	filename = substitute(ft_substr(cmd_str, i, j - i), misc, false);
	if (!filename)
		return (set_statcode(MALLOC_FAIL, misc), -1);
	if (sort_redirect(filename, type, cmd, misc) != EXIT_SUCCESS)
		return (-1);
	while (i < j)
		cmd_str[i++] = ' ';
	return (j - 1);
}

int	redirect_parsing(char *cmd_str, t_command *cmd, t_misc *misc)
{
	int	i;

	i = -1;
	while (cmd_str[++i])
	{
		i = quote_skip(cmd_str, i);
		if (cmd_str[i] == '>' || cmd_str[i] == '<')
			i = filename_parsing(cmd_str, i, cmd, misc);
		if (i == -1)
			return (delete_tmpfiles(misc), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
