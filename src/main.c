/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:29 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/18 18:11:33 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	use_input(char *input, t_misc *misc)
{
	add_history(input);
	misc->cmd_list = parse_input(input, misc);
	free(input);
	if (!misc->cmd_list)
		return ;
	g_status = command_handler(misc);
	ft_lstclear(&misc->cmd_list, free_command);
	delete_tmpfiles(misc);
}

static void	create_prompt(t_misc *misc)
{
	char	*input;

	while (!misc->exit_flag)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		if (misc->delet_this)
		{
			input = misc->delet_this;
			misc->exit_flag = true;
		}
		else
			input = readline("\001\033[32m\002Minishell $> \001\e[0m\022\002");
		if (!input)
			return ;
		if (*input)
			use_input(input, misc);
		else
			free(input);
	}
}

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

	if (argc > 2 && ft_strncmp(argv[1], "-c", 3) == 0)
		misc.delet_this = ft_strdup(argv[2]);
	else
		misc.delet_this = NULL;
	g_status = create_envp(envp, &misc);
	if (g_status == ENOMEM)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	misc.cmd_list = NULL;
	misc.tmpfile_count = 0;
	getcwd(misc.tmpfile_dir, PATH_MAX);
	misc.exit_flag = false;
	create_prompt(&misc);
	free_envp(misc.envp);
	clear_history();
	if (!misc.delet_this)
		ft_dprintf(2, "%sexit minishell\n%s", RED, RST);
	return (g_status);
}
