/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:50:01 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/24 14:33:52 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char *input)
{
	size_t	i;
	int		newline;

	newline = true;
	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '-' && input[i + 1] == 'n'
		&& (input[i + 2] == ' ' || input[i + 2] == '\0'))
	{
		newline = false;
		i += 2;
		while (input[i] && input[i] == ' ')
			i++;
	}
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
