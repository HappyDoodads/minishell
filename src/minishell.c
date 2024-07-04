#include "minishell.h"

void	ft_create_prompt(t_misc *misc)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = readline("\001\033[32m\002 Minishell $> \001\e[0m\022\002");
		if (!input)
			exit (0);
		else if (*input)
		{
			add_history(input);
			misc->cmd_list = parse_input(input, misc);
			free(input);
			if (!misc->cmd_list)
			{
				misc->prev_status = EXIT_FAILURE;
				continue ;
			}
			misc->prev_status = command_handler(misc);
			ft_lstclear(&misc->cmd_list, free_command);
			delete_tmpfiles(misc);
		}
		else
			free(input);
	}
}

static void	forking(t_list *cmd_list, t_misc *misc)
{
	static int	old_fd = 0;
	int			pipefd[2];
	t_command	*cmd;

	cmd = cmd_list->data;
	cmd->rd_fd = old_fd;
	cmd->wr_fd = 1;
	if (cmd_list->next != NULL)
	{
		pipe(pipefd);
		cmd->wr_fd = pipefd[1];
	}
	signal(SIGINT, sig_child_handler);
	cmd->pid = fork();
	if (cmd->pid == 0)
		exec_command(cmd, misc);
	ft_close(old_fd);
	if (cmd_list->next != NULL)
	{
		ft_close(pipefd[1]);
		old_fd = pipefd[0];
	}
	else
		old_fd = 0;
}

int	command_handler(t_misc *misc)
{
	t_list		*cmd_node;
	t_command	*cmd;
	int			status;

	cmd_node = misc->cmd_list;
	status = -1;
	if (cmd_node->next == NULL)
		status = exec_builtin(cmd_node->data, misc);
	if (status >= 0)
		return (status);
	while (cmd_node != NULL)
	{
		forking(cmd_node, misc);
		cmd_node = cmd_node->next;
	}
	cmd_node = misc->cmd_list;
	while (cmd_node != NULL)
	{
		cmd = cmd_node->data;
		waitpid(cmd->pid, &status, 0);
		cmd_node = cmd_node->next;
	}
	return (status);
}
