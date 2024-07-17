/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:29 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/17 13:08:08 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_envp(char **arg_envp, t_misc *misc)
{
	int		i;
	u_int	j;

	misc->envp_size = 0;
	while (arg_envp[misc->envp_size])
		misc->envp_size++;
	misc->envp_size += 6;
	misc->envp = ft_calloc(misc->envp_size, sizeof(t_envp));
	if (!misc->envp)
		return (ENOMEM);
	i = -1;
	while (arg_envp[++i])
	{
		j = 0;
		while (arg_envp[i][j] && arg_envp[i][j] != '=')
			j++;
		misc->envp[i].name = ft_substr(arg_envp[i], 0, j);
		if (!misc->envp[i].name)
			return (free_envp(misc->envp), ENOMEM);
		if (arg_envp[i][j])
			misc->envp[i].val = ft_strdup(&arg_envp[i][j + 1]);
		if (arg_envp[i][j] && !misc->envp[i].val)
			return (free_envp(misc->envp), ENOMEM);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_misc	misc;

	if (argc > 1)
		return (ft_dprintf(2, "%s: too many arguments\n", argv[0]), 1);
	misc.prev_status = create_envp(envp, &misc);
	if (misc.prev_status == ENOMEM)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	misc.cmd_list = NULL;
	misc.tmpfile_count = 0;
	getcwd(misc.tmpfile_dir, PATH_MAX);
	misc.exit_flag = false;
	ft_create_prompt(&misc);
	free_envp(misc.envp);
	clear_history();
	ft_dprintf(2, "%sexit minishell\n%s", RED, RST);
	return (misc.prev_status);
}
