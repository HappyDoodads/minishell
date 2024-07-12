/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:07 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 17:47:11 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isvalid_envname(const char *v_name, const char *context)
{
	int	i;

	i = 1;
	if (!ft_isalpha(v_name[0]) && v_name[0] != '_')
		return (print_err(context, v_name, "not a valid identifier"), false);
	while (ft_isalnum(v_name[i]) || v_name[i] == '_')
		i++;
	if (v_name[i] == '\0')
		return (true);
	return (print_err(context, v_name, "not a valid identifier"), false);
}

static void	unset_loopenv(t_envp *envp, const char *v_name)
{
	int		i;
	int		j;
	size_t	n;

	i = 0;
	n = ft_strlen(v_name) + 1;
	while (envp[i].name && ft_strncmp(envp[i].name, v_name, n) != 0)
		i++;
	if (!envp[i].name)
		return ;
	free(envp[i].name);
	free(envp[i].val);
	j = 1;
	while (envp[i + j].name)
		j++;
	ft_memmove(&envp[i], &envp[i + 1], sizeof(t_envp) * j);
}

int	ft_unset(t_command *cmd, t_misc *misc)
{
	int	i;
	int	status;

	i = 0;
	status = EXIT_SUCCESS;
	while (cmd->argv[++i])
	{
		if (ft_isvalid_envname(cmd->argv[i], "unset"))
			unset_loopenv(misc->envp, cmd->argv[i]);
		else
			status = EXIT_FAILURE;
	}
	return (status);
}
