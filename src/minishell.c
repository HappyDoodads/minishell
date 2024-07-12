/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:27 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 17:47:28 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_prompt(t_misc *misc)
{
	char	*input;

	while (!misc->exit_flag)
	{
		signal(SIGINT, sigint_handler);
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
		ft_memcpy(cmd->pipe_l, prev_cmd->pipe_r, sizeof (int [2]));
	}
	cmd->pipe_r[1] = 1;
	if (cmd_list->next)
		pipe(cmd->pipe_r);
	signal(SIGINT, sig_child_handler);
	signal(SIGQUIT, sig_child_handler);
	cmd->pid = fork();
	if (cmd->pid == 0)
		exec_command(cmd, misc);
	if (cmd_list->prev)
		close_pipe(prev_cmd->pipe_r);
}

static int	waitpid_loop(t_list *cmd_list)
{
	t_command	*cmd;
	int			stat;

	while (cmd_list)
	{
		cmd = cmd_list->data;
		waitpid(cmd->pid, &stat, 0);
		cmd_list = cmd_list->next;
	}
	if (WIFSIGNALED(stat))
		stat = 128 + WTERMSIG(stat);
	else if (!WIFEXITED(stat))
		stat = print_err("undefined behaviour", 0, "process stopping");
	else
		stat = WEXITSTATUS(stat);
	return (stat);
}

int	command_handler(t_misc *misc)
{
	t_list		*cmd_node;
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
	status = waitpid_loop(misc->cmd_list);
	return (status);
}
