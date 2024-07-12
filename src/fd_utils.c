/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:36 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 17:47:37 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_pipe(int pipefd[2])
{
	ft_close(pipefd[0]);
	ft_close(pipefd[1]);
}

void	close_cmd_pipes(t_command *cmd)
{
	close_pipe(cmd->pipe_l);
	close_pipe(cmd->pipe_r);
}
