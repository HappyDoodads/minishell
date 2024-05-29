/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:39 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/29 16:05:18 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_create_prompt(void)
{
	char	*input;
	t_list	*cmd_list;
	int		fd_arr[MAX_FD];

	while (1)
	{
		reset_fd_array(fd_arr);
		input = readline("\001\033[32m\002 Minishell $> \001\e[0m\022\002");
		if (input && *input)
			add_history(input);
		if (!input)
			break ;
		cmd_list = parse_input(input, fd_arr);
		free(input);
		command_handler(cmd_list, fd_arr);
		ft_lstclear(&cmd_list, free_command);
	}
}

int	command_handler(t_list **cmd_list, int fd_arr[MAX_FD])
{
	t_list	*cmd;
	pid_t	pid;
	int		child_n;
	int		status;

	cmd = *cmd_list;
	status = -1;
	if (cmd->next == NULL)
		status = exec_builtin(cmd->data, cmd_list);
	if (status >= 0)
		return (status);
	child_n = 0;
	while (cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
			exec_command(cmd->data, fd_arr, cmd_list);
		child_n++;
		cmd = cmd->next;
	}
	close_all(fd_arr, -1, -1);
	while (child_n-- > 0)
		wait(&status);
	return (status);
}

// int	command_handler(char *input)
// {
// 	if (ft_strncmp(input, "pwd", 3) == 0)
// 		ft_pwd();
// 	else if (ft_strncmp(input, "exit", 4) == 0)
// 		ft_exit(input);
// 	else if (ft_strncmp(input, "echo", 4) == 0)
// 		ft_echo(input);
// 	// else if (ft_strncmp(input, "cd", 2) == 0)
// 	// 	//TODO
// 	// else if (ft_strncmp(input, "export", 6) == 0)
// 	// 	//TODO
// 	// else if (ft_strncmp(input, "unset", 5) == 0)
// 	// 	//TODO
// 	// else if (ft_strncmp(input, "env", 3) == 0)
// 	// 	//TODO
// 	else
// 		printf("%sCommand not found%s\n", BLUE, RST);
// 	return (0);
// }
