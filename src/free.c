/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:34 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/22 14:31:53 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(void *data)
{
	t_command	*command;

	command = data;
	ft_free_split(command->argv);
	free(command->infile);
	free(command->outfile);
	free(data);
}

void	free_heredoc(void *data)
{
	t_heredoc	*heredoc;

	heredoc = data;
	free(heredoc->eof);
	free(heredoc->file);
}

void	free_envp(t_envp *envp)
{
	int	i;

	i = -1;
	while (envp[++i].name)
	{
		free(envp[i].name);
		free(envp[i].val);
	}
	ft_bzero(envp, i * sizeof(t_envp));
	free(envp);
}

void	cleanup(t_misc *misc)
{
	ft_lstclear(&misc->cmd_list, free_command);
	ft_lstclear(&misc->heredoc_list, free);
	free_envp(misc->envp);
	rl_clear_history();
}

void	delete_tmpfiles(t_misc *misc)
{
	char	file[PATH_MAX];
	char	*num;
	size_t	buf_left;

	if (misc->tmpfile_count == 0)
		return ;
	ft_strlcpy(file, misc->tmpfile_path, PATH_MAX);
	buf_left = ft_strlen(file);
	num = file + buf_left;
	buf_left = PATH_MAX - buf_left;
	while (misc->tmpfile_count > 0)
	{
		ft_itoab(--misc->tmpfile_count, num, buf_left);
		if (unlink(file) == -1)
			print_err(file, NULL, NULL);
	}
}
