/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:37 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/28 15:00:26 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	if (dup2(0, STDIN_DUP) != STDIN_DUP || dup2(1, STDOUT_DUP) != STDOUT_DUP)
		return (ft_dprintf(2, "Could not dup stdin or stdout\n"), EXIT_FAILURE);
	ft_create_prompt();
	return (EXIT_SUCCESS);
}
