/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:27 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/18 14:16:48 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	empty_cmd_check(t_misc *misc)
{
	t_list		*cmd_list;
	t_command	*cmd;

	cmd_list = misc->cmd_list;
	while (cmd_list)
	{
		cmd = cmd_list->data;
		if (!cmd->argv[0] && !cmd->infile && !cmd->outfile)
		{
			if (misc->cmd_list->next)
				return (print_err(NULL, NULL, "syntax error"), 2);
			return (g_status);
		}
		cmd_list = cmd_list->next;
	}
	return (-1);
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
			g_status = command_handler(misc);
			ft_lstclear(&misc->cmd_list, free_command);
			delete_tmpfiles(misc);
		}
		else
			free(input);
	}
}

int	command_handler(t_misc *misc)
{
	t_list		*cmd_node;
	int			status;

	status = empty_cmd_check(misc);
	if (status >= 0)
		return (status);
	cmd_node = misc->cmd_list;
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
