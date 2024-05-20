/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:39 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/17 16:33:49 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("\001\033[32m\002 Minishell $> \001\e[0m\022\002");
		if (input && *input)
			add_history(input);
		if (!input)
			break ;
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
	else if (ft_strncmp(input, "echo", 4) == 0)
		ft_echo(input);
	// else if (ft_strncmp(input, "cd", 2) == 0)
	// 	//TODO
	// else if (ft_strncmp(input, "export", 6) == 0)
	// 	//TODO
	// else if (ft_strncmp(input, "unset", 5) == 0)
	// 	//TODO
	// else if (ft_strncmp(input, "env", 3) == 0)
	// 	//TODO
	else
		printf("%sCommand not found%s\n", BLUE, RST);
	return (0);
}
