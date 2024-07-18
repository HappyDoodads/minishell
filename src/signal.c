/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:20 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/18 14:48:08 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	g_status = EXIT_FAILURE;
	rl_redisplay();
}

void	sig_child_handler(int sig_num)
{
	if (sig_num == 3)
		ft_putstr_fd("Quit: 3", 1);
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}
