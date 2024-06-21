#include "minishell.h"

void	ft_create_prompt(t_misc *misc)
{
	char	*input;

	while (1)
	{
		reset_fd_array(misc->fd_arr);
		input = readline("\001\033[32m\002 Minishell $> \001\e[0m\022\002");
		if (!input)
			ft_putendl_fd("readline error", 2);
		else if (*input)
		{
			add_history(input);
			misc->cmd_list = parse_input(input, misc->fd_arr);
			free(input);
			misc->prev_status = command_handler(misc);
			ft_lstclear(&misc->cmd_list, free_command);
		}
		else
			free(input);
	}
}

int	command_handler(t_misc *misc)
{
	t_list	*cmd;
	pid_t	pid;
	int		child_n;
	int		status;

	cmd = misc->cmd_list;
	status = -1;
	if (cmd->next == NULL)
		status = exec_builtin(cmd->data, misc);
	if (status >= 0)
		return (status);
	child_n = 0;
	while (cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
			exec_command(cmd->data, misc);
		child_n++;
		cmd = cmd->next;
	}
	close_all(misc->fd_arr, -1, -1);
	while (child_n-- > 0)
		wait(&status);
	return (status);
}
