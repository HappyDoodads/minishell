/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:37 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/15 14:29:18 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*commande;

	commande = NULL;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		commande = readline("\033[1;32mminishell$ \033[0m");
		if (strncmp(commande, "exit", 4) == 0)
		{
			free(commande);
			printf("%sexit minishell\n%s", RED, RST);
			exit(EXIT_SUCCESS);
		}
		printf("%scommande not found%s\n", BLUE, RST);
		free(commande);
	}
	return (0);
}
