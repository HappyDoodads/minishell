/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:31 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/18 21:03:45 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_loop(const char *eof, const char *file, t_misc *misc)
{
	char	*input;
	int		fd;
	int		eof_len;

	signal(SIGINT, SIG_DFL);
	eof_len = ft_strlen(eof);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (print_err(file, NULL, NULL));
	while (1)
	{
		ft_putstr_fd("> ", 1);
		input = get_next_line(0);
		if (!input)
			break ;
		if (ft_strncmp(input, eof, eof_len) == 0 && input[eof_len] == '\n')
		{
			free(input);
			break ;
		}
		input = substitute(input, misc, true, false);
		ft_putstr_fd(input, fd);
		free(input);
	}
	return (close(fd), EXIT_SUCCESS);
}

static int	fork_handler(const char *eof, const char *file, t_misc *misc)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_err("fork", NULL, NULL));
	if (pid == 0)
	{
		status = heredoc_loop(eof, file, misc);
		cleanup(misc);
		exit(status);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (ft_putchar_fd('\n', 1), EXIT_FAILURE);
	status = WEXITSTATUS(status);
	return (status);
}

int	heredoc_fork(const char *eof, int i, t_misc *misc)
{
	char	file[PATH_MAX];
	char	num[12];

	ft_strlcpy(file, misc->tmpfile_path, PATH_MAX);
	ft_itoab(i, num, 12);
	ft_strlcat(file, num, PATH_MAX);
	return (fork_handler(eof, file, misc));
}

char	*ft_heredoc(char *eof, t_misc *misc)
{
	char	*file;
	char	buf[12];
	t_list	*node;

	ft_itoab(ft_lstsize(misc->eof_list), buf, 12);
	file = ft_strjoin(misc->tmpfile_path, buf);
	if (!file)
		return (free(eof), print_err("malloc", NULL, NULL), NULL);
	node = ft_lstnew(eof);
	if (!node)
		return (free(file), free(eof), print_err("malloc", 0, 0), NULL);
	ft_lstadd_back(&misc->eof_list, node);
	return (file);
}
