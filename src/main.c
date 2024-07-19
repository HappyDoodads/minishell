/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:29 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/19 13:18:29 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	use_input(char *input, t_misc *misc)
{
	t_list	*eof_node;

	if (!*input)
		return (free(input));
	add_history(input);
	misc->cmd_list = parse_input(input, misc);
	free(input);
	if (!misc->cmd_list)
		return ;
	eof_node = misc->eof_list;
	while (eof_node)
	{
		if (heredoc_fork(eof_node->data, misc->tmpfile_count, misc) != 0)
			return ;
		misc->tmpfile_count++;
		eof_node = eof_node->next;
	}
	g_status = command_handler(misc);
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
		use_input(input, misc);
		if (misc->cmd_list)
			ft_lstclear(&misc->cmd_list, free_command);
		if (misc->eof_list)
			ft_lstclear(&misc->eof_list, free);
		delete_tmpfiles(misc);
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
	else if (argc == 1)
		misc.delet_this = NULL;
	else
	{
		print_err(argv[1], NULL, "invalid option");
		return (ft_dprintf(2, "Usage: %s [-c input]", argv[0]), 2);
	}
	g_status = create_envp(envp, &misc);
	if (g_status == ENOMEM)
		return (print_err("malloc", NULL, NULL), ENOMEM);
	misc.cmd_list = NULL;
	misc.eof_list = NULL;
	getcwd(misc.tmpfile_path, PATH_MAX);
	ft_strlcat(misc.tmpfile_path, "/.tmp", PATH_MAX);
	misc.exit_flag = false;
	misc.tmpfile_count = 0;
	create_prompt(&misc);
	cleanup(&misc);
	if (!misc.delet_this)
		ft_dprintf(2, "%sexit minishell\n%s", RED, RST);
	return (g_status);
}
