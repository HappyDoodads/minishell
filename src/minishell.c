#include "minishell.h"

void	ft_create_prompt(t_misc *misc)
{
	char	*input;

	while (!misc->exit_flag)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\001\033[32m\002Minishell $> \001\e[0m\022\002");
		if (!input)
			return ;
		if (*input)
		{
			add_history(input);
			misc->cmd_list = parse_input(input, misc);
			free(input);
			if (!misc->cmd_list)
				continue ;
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
	t_command	*prev_cmd;
	t_command	*cmd;

	cmd = cmd_list->data;
	if (cmd_list->prev)
	{
		prev_cmd = cmd_list->prev->data;
		ft_memcpy(cmd->pipe_L, prev_cmd->pipe_R, sizeof(int[2]));
	}
	cmd->pipe_R[1] = 1;
	if (cmd_list->next)
		pipe(cmd->pipe_R);
	signal(SIGINT, sig_child_handler);
	signal(SIGQUIT, sig_child_handler);
	cmd->pid = fork();
	if (cmd->pid == 0)
		exec_command(cmd, misc);
	if (cmd_list->prev)
		close_pipe(prev_cmd->pipe_R);
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
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else
		status = WEXITSTATUS(status);
	return (status);
}
