#include "minishell.h"

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
	//signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, sigquit_handler);
	if (argc > 1)
		return (ft_dprintf(2,"%s: too many arguments\n" , argv[0]), 1);
	if (dup2(0, STDIN_DUP) != STDIN_DUP || dup2(1, STDOUT_DUP) != STDOUT_DUP)
		return (ft_dprintf(2, "Could not dup stdin or stdout\n"), EXIT_FAILURE);
	misc.envp = dup_envp(envp);
	misc.prev_status = 0;
	misc.cmd_list = NULL;
	ft_create_prompt(&misc);
	return (EXIT_SUCCESS);
}
