/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:00:00 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/24 14:34:06 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(char *input)
{
	free(input);
	printf("%sexit minishell\n%s", RED, RST);
	exit(EXIT_SUCCESS);
}
