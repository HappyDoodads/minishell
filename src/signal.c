#include "minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_child_handler(int sig_num)
{
	(void)sig_num;
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}

void	sig_heredoc_handler(int sig_num)
{
	(void)sig_num;

	ft_putchar_fd('\n', 1);
	exit(2);
}
