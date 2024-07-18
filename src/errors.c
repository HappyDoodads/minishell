/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:49 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/18 17:00:05 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err(const char *s1, const char *s2, const char *msg)
{
	if (!msg)
		msg = strerror(errno);
	if (!s1 && !s2)
		ft_dprintf(2, "minishell: %s\n", msg);
	else if (!s2)
		ft_dprintf(2, "minishell: %s: %s\n", s1, msg);
	else if (!s1)
		ft_dprintf(2, "print_error_msg: s1 cannot be NULL if s2 is not NULL\n");
	else
		ft_dprintf(2, "minishell: %s: %s: %s\n", s1, s2, msg);
	return (EXIT_FAILURE);
}

void	set_stat(int errnum)
{
	g_status = errnum;
}

int	execve_errno(const char *cmd_name)
{
	if (errno == ENOENT)
		return (print_err(cmd_name, NULL, "command not found"), 127);
	if (errno == EACCES)
		return (print_err(cmd_name, NULL, NULL), 126);
	return (EXIT_FAILURE);
}
