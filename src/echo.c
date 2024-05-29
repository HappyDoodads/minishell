/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:50:01 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/29 15:24:35 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	write_echo(char *input)
// {
// 	size_t	i;
// 	int		newline;

// 	newline = true;
// 	i = 0;
// 	while (input[i] && input[i] == ' ')
// 		i++;
// 	if (input[i] == '-' && input[i + 1] == 'n'
// 		&& (input[i + 2] == ' ' || input[i + 2] == '\0'))
// 	{
// 		newline = false;
// 		i += 2;
// 		while (input[i] && input[i] == ' ')
// 			i++;
// 	}
// 	while (input[i])
// 	{
// 		write(1, &input[i], 1);
// 		i++;
// 	}
// 	if (newline)
// 		write(1, "\n", 1);
// }

int	ft_echo(t_command *cmd)
{
	unsigned int	i;
	void	(*print_func)(char *, int);

	print_func = ft_putendl_fd;
	i = 1;
	if (cmd->argv[i] == NULL)
		ft_putchar_fd('\n', 1);
	else if (ft_strncmp(cmd->argv[i], "-n", 3) == 0)
	{
		print_func = ft_putstr_fd;
		i++;
	}
	while (cmd->argv[i] != NULL)
		print_func(cmd->argv[i++], cmd->wr_fd);
	return (0);
}