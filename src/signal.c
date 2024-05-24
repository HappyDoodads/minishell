/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:09:04 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/24 14:34:25 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal, siginfo_t *info, void *ucontext)
{
	struct sigaction	sa;

	(void)*info;
	(void)*ucontext;
	if (signal == SIGINT)
	{
		ft_printf("\n");
		ft_create_prompt();
		// sa.sa_handler = SIG_DFL;
		// sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
	}
}

void	sigint_handler(int sig)
{
	struct sigaction	sa;

	(void)sig;
	printf("\n");
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
	sigaction(SIGUSR2, &sa, NULL) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
