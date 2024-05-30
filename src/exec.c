/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:24:10 by jdemers           #+#    #+#             */
/*   Updated: 2024/05/30 19:31:59 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_fullpath(char *name)
{
	return (ft_strdup(name));
}

int	exec_builtin(t_command *command, t_misc *misc)
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
		status = ft_exit(command, misc);
	else
		return (-1);
	return (status);
}

void	exec_command(t_command *command, t_misc *misc)
{
	char	*full_path;
	int		status;

	close_all(misc->fd_arr, command->wr_fd, command->rd_fd);
	status = exec_builtin(command, misc);
	if (status == -1)
	{
		full_path = get_fullpath(command->argv[0]);
		execve(full_path, command->argv, NULL);
		free(full_path);
		status = errno;
	}
	close(command->rd_fd);
	close(command->wr_fd);
	ft_lstclear(&misc->cmd_list, free_command);
	exit(status);
}