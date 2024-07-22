/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:47:31 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/22 15:04:29 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_has_quotes(const char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == SQUOTE || arg[i] == DQUOTE)
			return (true);
	}
	return (false);
}

static int	heredoc_loop(t_heredoc *heredoc, int fd, t_misc *misc)
{
	char	*input;
	int		eof_len;

	signal(SIGINT, SIG_DFL);
	eof_len = ft_strlen(heredoc->eof);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		input = get_next_line(0);
		if (!input)
			break ;
		if (!ft_strncmp(input, heredoc->eof, eof_len) && input[eof_len] == '\n')
		{
			free(input);
			break ;
		}
		if (!heredoc->has_quotes)
			input = substitute(input, misc, IN_HEREDOC);
		if (!input)
			return (close(fd), print_err("malloc", NULL, NULL), ENOMEM);
		ft_putstr_fd(input, fd);
		free(input);
	}
	return (close(fd), EXIT_SUCCESS);
}

int	heredoc_fork(t_heredoc *heredoc, t_misc *misc)
{
	int		status;
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_err("fork", NULL, NULL));
	if (pid == 0)
	{
		fd = open(heredoc->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			status = print_err(heredoc->file, NULL, NULL);
		else
			status = heredoc_loop(heredoc, fd, misc);
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

char	*ft_heredoc(char *eof, t_misc *misc)
{
	char		*file;
	char		buf[12];
	t_list		*node;
	t_heredoc	*heredoc;

	ft_itoab(ft_lstsize(misc->heredoc_list), buf, 12);
	file = ft_strjoin(misc->tmpfile_path, buf);
	heredoc = ft_calloc(1, sizeof(t_heredoc));
	node = ft_lstnew(heredoc);
	if (!file || !heredoc || !node)
	{
		print_err("malloc", 0, 0);
		return (free(file), free(eof), free(heredoc), free(node), NULL);
	}
	heredoc->has_quotes = ft_has_quotes(eof);
	heredoc->file = ft_strdup(file);
	heredoc->eof = substitute(eof, misc, NO_SUBST);
	if (!heredoc->file || !heredoc->eof)
		return (ft_lstdelone(node, free_heredoc), free(file), NULL);
	ft_lstadd_back(&misc->heredoc_list, node);
	return (file);
}
