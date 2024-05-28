/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:09:31 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/28 14:24:27 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_command(void *data)
{
	t_command	*command;

	command = data;
	ft_free_split(command->argv);
	command->rd_fd = -1;
	command->wr_fd = -1;
	free(data);
}