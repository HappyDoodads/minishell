/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:04:52 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/28 15:54:49 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_fd_array(int fd_arr[MAX_FD])
{
	int	i;

	i = 0;
	while (i < MAX_FD)
		fd_arr[i++] = -1;
	fd_arr[0] = 0;
	dup2(STDIN_DUP, 0);
	dup2(STDOUT_DUP, 1);
}

void	add_fd(int fd_arr[MAX_FD], int fd)
{
	int	i;

	if (fd < 0)
	{
		ft_printf("ERROR: %d is not a valid file descriptor\n", fd);
		return ;
	}
	i = 0;
	while (fd_arr[i] != -1 && i < MAX_FD - 1)
		i++;
	if (i == MAX_FD - 1)
		ft_printf("ERROR: TOO MANY FD\n");
	else
	{
		fd_arr[i++] = fd;
		fd_arr[i] = -1;
	}
}

int	get_last_fd(int fd_arr[MAX_FD])
{
	int	i;

	i = 0;
	while (fd_arr[i] != -1)
		i++;
	return (i - 1);
}

int	close_all(int fd_arr[MAX_FD], int fd1, int fd2)
{
	int	i;

	i = -1;
	while (fd_arr[++i] != -1)
	{
		if (fd_arr[i] != fd1 && fd_arr[i] != fd2)
			close(fd_arr[i]);
	}
	return (0);
}