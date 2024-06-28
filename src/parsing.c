#include "minishell.h"

int	quote_skip(char *line, int i)
{
	char	quote;

	if (line[i] != QUOTE && line[i] != DQUOTE)
		return (i);
	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		return (i);
	print_err(NULL, NULL, "Opened quotes must always be closed");
	return (-1);
}

//	TODO: Gestion d'erreur
static void	parse_cmd(char *cmd_str, t_list **cmd_list, t_misc *misc)
{
	t_command	*command;
	t_list		*new;

	command = ft_calloc(1, sizeof(t_command));
	redirect_parsing(cmd_str, command, misc);
	command->argv = split_args(cmd_str);
	new = ft_lstnew(command);
	ft_lstadd_back(cmd_list, new);
	free(cmd_str);
}

t_list	*parse_input(char *input, t_misc *misc)
{
	t_list			*cmd_list;
	unsigned int	start;
	int				i;

	i = -1;
	start = 0;
	cmd_list = NULL;
	while (input[++i])
	{
		i = quote_skip(input, i);
		if (i == -1)
			return (ft_lstclear(&cmd_list, free_command), NULL);
		if (input[i] == '|')
		{
			parse_cmd(ft_substr(input, start, i - start), &cmd_list, misc);
			start = i + 1;
		}
	}
	parse_cmd(ft_substr(input, start, i - start), &cmd_list, misc);
	return (cmd_list);
}
