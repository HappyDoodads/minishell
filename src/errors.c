/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:49 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 17:47:50 by jdemers          ###   ########.fr       */
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

void	set_statcode(int errnum, t_misc *misc)
{
	misc->prev_status = errnum;
}

int	execve_errno(void)
{
	if (errno == ENOENT)
		return (127);
	return (1);
}
