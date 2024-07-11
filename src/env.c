#include "minishell.h"

static void	print_env_var(t_envp env_v, int fd_out)
{
	if (!env_v.val)
		ft_dprintf(fd_out, "%s\n", env_v.name);
	else if (!env_v.val[0])
		ft_dprintf(fd_out, "%s=''\n", env_v.name);
	else
		ft_dprintf(fd_out, "%s=%s\n", env_v.name, env_v.val);
}

static t_envp	seek_next_print(const t_envp *envp, const char *prev_n, int fd)
{
	int		i;
	int		j;
	size_t	n;

	i = 0;
	n = ft_strlen(prev_n) + 1;
	while (ft_strncmp(envp[i].name, prev_n, n) <= 0)
		i++;
	j = i;
	while (envp[++j].name)
	{
		n = ft_strlen(envp[j].name) + 1;
		if (ft_strncmp(envp[i].name, envp[j].name, n) > 0
				&& ft_strncmp(envp[j].name, prev_n, n) > 0)
			i = j;
	}
	print_env_var(envp[i], fd);
	return (envp[i]);
}

void	ascii_sort(const t_envp *envp, int fd_out)
{
	t_envp	prev;
	u_int	to_print;

	if (!envp[0].name)
		return ;
	prev = seek_next_print(envp, "", fd_out);
	to_print = 0;
	while (envp[to_print + 1].name)
		to_print++;
	while (to_print-- > 0)
		prev = seek_next_print(envp, prev.name, fd_out);
}

int	ft_env(t_command *cmd, t_misc *misc)
{
	int	i;

	i = 0;
	while (misc->envp[i].name)
		print_env_var(misc->envp[i++], cmd->pipe_R[1]);
	return (EXIT_SUCCESS);
}
