#include "minishell.h"

char	**ss_envp_creat(const t_envp *envp)
{
	char	**ss_envp;
	size_t	i;

	i = 0;
	while (envp[i].name)
		i++;
	ss_envp = ft_calloc(i + 1, sizeof(char *));
	if (!ss_envp)
		return (print_err("malloc", NULL, NULL), NULL);
	i = 0;
	while (envp->name)
	{
		if (!envp->val)
			ss_envp[i] = ft_strdup(envp->name);
		else if (!envp->val[0])
			ss_envp[i] = ft_strjoin(envp->name, "=");
		else
			ss_envp[i] = ft_str3join(envp->name, "=", envp->val);
		if (!ss_envp[i++])
			return (print_err("malloc", 0, 0), ft_free_split(ss_envp));
		envp++;
	}
	return (ss_envp);
}

static t_envp	seek_next_print(const t_envp *envp, const char *prev_n, int out)
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
	if (!envp[i].val)
		ft_dprintf(out, "declare -x %s\n", envp[i].name);
	else if (!envp[i].val[0])
		ft_dprintf(out, "declare -x %s=''\n", envp[i].name);
	else
		ft_dprintf(out, "declare -x %s=%s\n", envp[i].name, envp[i].val);
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

const char	*envp_getval(const t_envp *envp, const char *v_name)
{
	size_t	n;

	n = ft_strlen(v_name) + 1;
	while (envp->name && ft_strncmp(v_name, envp->name, n) != 0)
		envp++;
	if (!envp->val)
		return ("");
	return (envp->val);
}

int	ft_env(t_command *cmd, t_misc *misc)
{
	int	i;
	int	out;

	i = -1;
	out = cmd->pipe_R[1];
	while (misc->envp[++i].name)
	{
		if (!misc->envp[i].val)
			continue ;
		else if (!misc->envp[i].val[0])
			ft_dprintf(out, "%s=\n", misc->envp[i].name);
		else
			ft_dprintf(out, "%s=%s\n", misc->envp[i].name, misc->envp[i].val);
	}
	return (EXIT_SUCCESS);
}
