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
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
	}
	if (!fullpath)
		fullpath = ft_strdup(name + 1);
	return (ft_free_split(paths), free(name), fullpath);
}

static int	open_redirections(t_command *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
			return (print_err(cmd->infile, NULL, NULL));
		close(cmd->pipe_L[0]);
		cmd->pipe_L[0] = fd;
	}
	if (cmd->outfile)
	{
		if (cmd->append_out)
			fd = open(cmd->outfile, O_WRONLY|O_APPEND|O_CREAT, 420);
		else
			fd = open(cmd->outfile, O_WRONLY|O_TRUNC|O_CREAT, 420);
		if (fd == -1)
			return (print_err(cmd->outfile, NULL, NULL));
		ft_close(cmd->pipe_R[1]);
		cmd->pipe_R[1] = fd;
	}
	return (EXIT_SUCCESS);
}

int	exec_builtin(t_command *cmd, t_misc *misc)
{
	const char	*name;
	int			(*builtin)(t_command *, t_misc *);

	name = cmd->argv[0];
	if (!name)
		return (open_redirections(cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		builtin = ft_cd;
	else if (ft_strncmp(name, "echo", 5) == 0)
		builtin = ft_echo;
	else if (ft_strncmp(name, "env", 4) == 0)
		builtin = ft_env;
	else if (ft_strncmp(name, "export", 7) == 0)
		builtin = ft_export;
	else if (ft_strncmp(name, "pwd", 4) == 0)
		builtin = ft_pwd;
	else if (ft_strncmp(name, "unset", 6) == 0)
		builtin = ft_unset;
	else if (ft_strncmp(name, "exit", 5) == 0)
		builtin = ft_exit;
	else
		return (-1);
	if (open_redirections(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (builtin(cmd, misc));
}

void	exec_command(t_command *cmd, t_misc *misc)
{
	char	*fullpath;
	int		status;

	status = exec_builtin(cmd, misc);
	if (status == -1 && open_redirections(cmd) == EXIT_SUCCESS)
	{
		dup2(cmd->pipe_L[0], 0);
		dup2(cmd->pipe_R[1], 1);
		close_pipe(cmd->pipe_L);
		close_pipe(cmd->pipe_R);
		fullpath = get_fullpath(cmd->argv[0], misc->envp);
		execve(fullpath, cmd->argv, misc->envp);
		free(fullpath);
		status = errno;
	}
	else if (status == -1)
		status = EXIT_FAILURE;
	else
	{
		close_pipe(cmd->pipe_L);
		close_pipe(cmd->pipe_R);
	}
	cleanup(misc);
	exit(status);
}
