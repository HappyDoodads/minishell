/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:38 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 17:47:39 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_export(t_envp *env_v, const char *v_val)
{
	free(env_v->val);
	if (v_val)
	{
		env_v->val = ft_strdup(v_val);
		if (!env_v->val)
			return (print_err("malloc", NULL, NULL), ENOMEM);
	}
	else
		env_v->val = NULL;
	return (EXIT_SUCCESS);
}

static int	new_export(t_envp *env_v, const char *v_name, const char *v_val)
{
	env_v->name = ft_strdup(v_name);
	if (!env_v->name)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	if (!v_val)
		return (EXIT_SUCCESS);
	env_v->val = ft_strdup(v_val);
	if (!env_v->val)
	{
		free(env_v->name);
		env_v->name = NULL;
		return (print_err("malloc", NULL, NULL), ENOMEM);
	}
	return (EXIT_SUCCESS);
}

int	export_loopenv(t_misc *misc, const char *v_name, const char *v_val)
{
	int		j;
	size_t	vn_len;
	t_envp	*tmp;

	j = -1;
	vn_len = ft_strlen(v_name) + 1;
	while (misc->envp[++j].name)
	{
		if (ft_strncmp(misc->envp[j].name, v_name, vn_len) == 0)
			return (update_export(&misc->envp[j], v_val));
	}
	if (j == misc->envp_size)
	{
		tmp = ft_calloc(misc->envp_size + 5, sizeof(t_envp));
		if (!tmp)
			return (print_err("malloc", NULL, NULL), ENOMEM);
		misc->envp_size += 5;
		ft_memcpy(tmp, misc->envp, sizeof(t_envp) * (j - 1));
		free(misc->envp);
		misc->envp = tmp;
	}
	return (new_export(&misc->envp[j], v_name, v_val));
}

static int	get_export_var(t_misc *misc, const char *export)
{
	char	*v_name;
	u_int	len;
	int		status;

	len = 0;
	while (export[len] && export[len] != '=')
		len++;
	v_name = ft_substr(export, 0, len);
	if (!v_name)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	if (!ft_isvalid_envname(v_name, "export"))
		status = EXIT_FAILURE;
	else if (export[len])
		status = export_loopenv(misc, v_name, &export[len + 1]);
	else
		status = export_loopenv(misc, v_name, NULL);
	free(v_name);
	return (status);
}

int	ft_export(t_command *cmd, t_misc *misc)
{
	int	i;
	int	status;

	i = 0;
	if (cmd->argv[1] == NULL)
		return (ascii_sort(misc->envp, cmd->pipe_r[1]), EXIT_SUCCESS);
	status = EXIT_SUCCESS;
	while (cmd->argv[++i] && status != ENOMEM)
		status = get_export_var(misc, cmd->argv[i]) || status;
	return (status);
}
