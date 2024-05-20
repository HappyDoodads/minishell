/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:39 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/17 10:07:22 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell $> ");
		if (input && *input)
			add_history(input);
		command_handler(input);
		free(input);
	}
}

int	command_handler(char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(input, "exit", 4) == 0)
		ft_exit(input);
	else
		printf("%sCommand not found%s\n", BLUE, RST);
	return (0);
}
