/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:42 by jcoquet           #+#    #+#             */
/*   Updated: 2024/06/05 09:05:14 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_skip(char *line, int i)
{
	char	quote;

	if (line[i] != QUOTE && line[i] != DQUOTE)
		return (i);
	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		return (i);
	return (-1);
}

//	TODO: Gestion d'erreur
static void	parse_cmd(char *cmd_str, t_list **cmd_list, int fd_arr[MAX_FD])
{
	int			pipefd[2];
	t_command	*command;
	t_list		*new;

	command = malloc(sizeof(t_command));
	if (fd_arr[0] == -1)
		command->rd_fd = 0;
	else
		command->rd_fd = get_last_fd(fd_arr);
	pipe(pipefd);
	command->wr_fd = pipefd[1];
	add_fd(fd_arr, pipefd[1]);
	add_fd(fd_arr, pipefd[0]);
	command->argv = split_args(cmd_str);
	new = ft_lstnew(command);
	ft_lstadd_back(cmd_list, new);
	free(cmd_str);
}

static void	parse_last_cmd(char *cmd_str, t_list **cmd_list, int fd_arr[MAX_FD])
{
	t_command	*command;
	t_list		*new;

	command = malloc(sizeof(t_command));
	command->rd_fd = get_last_fd(fd_arr);
	command->wr_fd = 1;
	command->argv = split_args(cmd_str);
	new = ft_lstnew(command);
	ft_lstadd_back(cmd_list, new);
	free(cmd_str);
}

t_list	*parse_input(char *input, int fd_arr[MAX_FD])
{
	t_list			*cmd_list;
	unsigned int	start;
	int				i;

	i = -1;
	start = 0;
	cmd_list = NULL;
	while (input[++i])
	{
		i = quote_skip(input, i);
		if (i == -1)
			return (ft_lstclear(&cmd_list, free_command), NULL);
		if (input[i] == '|')
		{
			parse_cmd(ft_substr(input, start, i - start), &cmd_list, fd_arr);
			start = i + 1;
		}
	}
	parse_last_cmd(ft_substr(input, start, i - start), &cmd_list, fd_arr);
	return (cmd_list);
}