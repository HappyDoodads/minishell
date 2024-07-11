#include "minishell.h"

void	ft_ascii_sort(t_command *cmd, t_misc *misc)
{
	int		i;
	char	*tmp;
	char	**cpy_envp;

	cpy_envp = dup_envp(misc->envp);
	i = 0;
	while (cpy_envp[i] && cpy_envp[i + 1])
	{
		if (ft_strncmp(cpy_envp[i], cpy_envp[i + 1], 1) > 0)
		{
			tmp = cpy_envp[i];
			cpy_envp[i] = cpy_envp[i + 1];
			cpy_envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (cpy_envp[i])
		ft_dprintf(cmd->pipe_R[1], "%s\n", cpy_envp[i++]);
	ft_free_split(cpy_envp);
}

