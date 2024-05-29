/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:00 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/28 19:22:03 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(char **argv, t_list **cmd_list)
{
	
	ft_dprintf(2, "%sexit minishell\n%s", RED, RST);
	exit(EXIT_SUCCESS);
}
