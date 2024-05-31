/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:24:10 by jdemers           #+#    #+#             */
/*   Updated: 2024/05/31 16:52:17 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_binpaths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i])
	{
		if (!envp[i][5])
			return (NULL);
		paths = ft_split(envp[i] + 5, ':');
		if (paths == NULL)
			return (perror("minishell"), NULL);
	}
	return (paths);
}

static char	*get_fullpath(char *name, char	**envp)
{
	char	*fullpath;
	char	**paths;
	int		i;

	paths = find_binpaths(envp);
	if (!paths)
		return (ft_strdup(name));
	name = ft_strjoin("/", name);
	if (!name)
		return (perror("minishell"), NULL);
	i = -1;
	while (paths[++i])
	{
		fullpath = ft_strjoin(paths[i], name);
		if (!fullpath)
			return (perror("minishell"), free(name), NULL);
		if (access(fullpath, X_OK) == true)
			break ;
		free(fullpath);
		fullpath = NULL;
	}
	if (!fullpath)
		fullpath = ft_strdup(name + 1);
	return (ft_free_split(paths), free(name), fullpath);
}

int	exec_builtin(t_command *command, t_misc *misc)
{
	const char	*name;
	int			status;

	name = command->argv[0];
	if (ft_strncmp(name, "cd", 3) == 0)
		status = ft_cd(command, misc);
	else if (ft_strncmp(name, "echo", 5) == 0)
		status = ft_echo(command);
	else if (ft_strncmp(name, "env", 4) == 0)
		status = ft_env(command, misc);
	else if (ft_strncmp(name, "export", 7) == 0)
		status = ft_export(command, misc);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		status = ft_pwd(command);
	else if (ft_strncmp(name, "unset", 6) == 0)
		status = ft_unset(command, misc);
	else if (ft_strncmp(name, "exit", 5) == 0)
		status = ft_exit(command, misc);
	else
		return (-1);
	return (status);
}

void	exec_command(t_command *command, t_misc *misc)
{
	char	*fullpath;
	int		status;

	close_all(misc->fd_arr, command->wr_fd, command->rd_fd);
	status = exec_builtin(command, misc);
	if (status == -1)
	{
		fullpath = get_fullpath(command->argv[0], misc->envp);
		dprintf(2, "fullpath='%s'\n", fullpath);
		execve(fullpath, command->argv, misc->envp);
		free(fullpath);
		status = errno;
	}
	close(command->rd_fd);
	close(command->wr_fd);
	ft_lstclear(&misc->cmd_list, free_command);
	exit(status);
}