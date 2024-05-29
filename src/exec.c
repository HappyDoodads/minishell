/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:24:10 by jdemers           #+#    #+#             */
/*   Updated: 2024/05/29 15:36:14 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_command *command, t_list **cmd_list)
{
	const char	*name;
	int			status;

	name = command->argv[0];
	if (ft_strncmp(name, "cd", 3) == 0)
		status = ft_cd(command);
	else if (ft_strncmp(name, "echo", 5) == 0)
		status = ft_echo(command);
	else if (ft_strncmp(name, "env", 4) == 0)
		status = ft_env(command);
	else if (ft_strncmp(name, "export", 7) == 0)
		status = ft_export(command);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		status = ft_pwd(command);
	else if (ft_strncmp(name, "unset", 6) == 0)
		status = ft_unset(command);
	else if (ft_strncmp(name, "exit", 5) == 0)
		ft_exit(command, cmd_list);
	else
		return (-1);
	return (status);
}

void	exec_command(t_command *command, int fd_arr[MAX_FD], t_list **cmd_list)
{
	char	*fullpath;
	int		status;

	close_all(fd_arr, command->wr_fd, command->rd_fd);
	status = find_command(command->argv, cmd_list);
	if (status == -1)
	{
		fullpath = get_fullpath(command->argv[0]);
		execve(fullpath, command->argv, get_envp());
		status = errno;
	}
	close(command->rd_fd);
	close(command->wr_fd);
	ft_lstclear(cmd_list, free_command);
	exit(status);
}