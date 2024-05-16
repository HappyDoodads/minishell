/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:37 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/16 17:01:08 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char		*input;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		input = readline("Minishell $ ");
		if (input && *input)
			add_history(input);
		if (input && ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			printf("%sexit minishell\n%s", RED, RST);
			exit(EXIT_SUCCESS);
		}
		printf("%sCommand not found%s\n", BLUE, RST);
		free(input);
	}
	return (EXIT_SUCCESS);
}
