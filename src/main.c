#include "minishell.h"

static t_envp	*create_envp(char **arg_envp)
{
	t_envp	*envp;
	int		i;
	u_int	j;

	i = 0;
	while (arg_envp[i])
		i++;
	envp = ft_calloc(i + 1, sizeof(t_envp));
	if (!envp)
		return (NULL);
	i = -1;
	while (arg_envp[++i])
	{
		j = 0;
		while (arg_envp[i][j] && arg_envp[i][j] != '=')
			j++;
		envp[i].name = ft_substr(arg_envp[i], 0, j);
		if (!envp[i].name)
			return (free_envp(envp), NULL);
		if (arg_envp[i][j])
			envp[i].val = ft_strdup(&arg_envp[i][j + 1]);
		if (arg_envp[i][j] && !envp[i].val)
			return (free_envp(envp), NULL);
	}
	return (envp);
}

char	**dup_envp(char **envp)
{
	char	**new;
	int		i;

	i = 1;
	while (envp[i - 1])
		i++;
	new = ft_calloc(i, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
			return (ft_free_split(new));
	}
	return (new);
}

int	main(int argc, char **argv, char **envp)
{
	t_misc	misc;

	signal(SIGQUIT, SIG_IGN);
	dprintf(2, "%sISSUE: <<eof cd [dir]\n%s", YELLOW, RST);
	if (argc > 1)
		return (ft_dprintf(2,"%s: too many arguments\n" , argv[0]), 1);
	misc.envp = dup_envp(envp);
	misc.prev_status = 0;
	misc.cmd_list = NULL;
	misc.tmpfile_count = 0;
	getcwd(misc.tmpfile_dir, PATH_MAX);
	ft_create_prompt(&misc);
	ft_free_split(misc.envp);
	clear_history();
	return (misc.prev_status);
}
